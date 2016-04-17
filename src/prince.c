
#include <base/game_const.h>
#include <base/game_ctx.h>
#include <base/collision.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmGroup.h>
#include <GFraMe/gfmSprite.h>

#include <jam/prince.h>
#include <jam/type.h>
#include <jam/slash.h>

enum {
    PRINCE_STAND = 0,
    PRINCE_WALK,
    PRINCE_SLASH,
    PRINCE_HURT,
    PRINCE_SHAPESHIFT
};

static int prince_data[] = {
/*                   len|fps|loop|data ... */
/*PRINCE_STAND     */1 , 0 , 0  , 32,
/*PRINCE_WALK      */4 , 8 , 1  , 33,32,34,32,
/*PRINCE_SLASH     */3 , 12, 0  , 35,36,37,
/*PRINCE_HURT      */1 , 0 , 0  , 32,
/*PRINCE_SHAPESHIFT*/1 , 0 , 0  , 32,
};
static int prince_data_len = sizeof(prince_data) / sizeof(int);

#define PLAY(anim) \
  do { \
    if (pGlobal->playerAnim != anim) { \
      rv = gfmSprite_playAnimation(pGlobal->pPlayer, anim); \
      ASSERT(rv == GFMRV_OK, rv); \
      pGlobal->playerAnim = anim; \
    } \
  } while(0)


static gfmRV prince_spawn_slash() {
    gfmRV rv;
    int x, y, flip;

    rv = gfmSprite_getPosition(&x, &y, pGlobal->pPlayer);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_getDirection(&flip, pGlobal->pPlayer);
    ASSERT(rv == GFMRV_OK, rv);

    if (flip) {
        x += PRINCE_SLASH_LOFFX;
    }
    else {
        x += PRINCE_SLASH_ROFFX;
    }
    y += PRINCE_SLASH_OFFY;


    rv = spawn_slash(x, y, flip);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_init() {
    gfmRV rv;

    pGlobal->playerAnim = -1;

    rv = gfmSprite_init(pGlobal->pPlayer, PRINCE_X, PRINCE_Y, PRINCE_W,
            PRINCE_H, PRINCE_SSET, PRINCE_OFFX, PRINCE_OFFY, 0/*child*/,
            T_PRINCE);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_addAnimations(pGlobal->pPlayer, prince_data,
            prince_data_len);
    ASSERT(rv == GFMRV_OK, rv);
    PLAY(PRINCE_STAND);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_update() {
    gfmRV rv;
    double vx;

    if (pGlobal->playerAnim == PRINCE_SLASH) {
        vx = 0;
    }
    else if (pButton->left.state & gfmInput_pressed) {
        vx = -PRINCE_VX;
        rv = gfmSprite_setDirection(pGlobal->pPlayer, 1);
        ASSERT(rv == GFMRV_OK, rv);
    }
    else if (pButton->right.state & gfmInput_pressed) {
        vx = PRINCE_VX;
        rv = gfmSprite_setDirection(pGlobal->pPlayer, 0);
        ASSERT(rv == GFMRV_OK, rv);
    }
    else {
        vx = 0;
    }
    rv = gfmSprite_setHorizontalVelocity(pGlobal->pPlayer, vx);
    ASSERT(rv == GFMRV_OK, rv);

    if ((pButton->act.state & gfmInput_justPressed) == gfmInput_justPressed) {
        if (pGlobal->playerAnim != PRINCE_SLASH) {
            rv = prince_spawn_slash();
            ASSERT(rv == GFMRV_OK, rv);
        }

        PLAY(PRINCE_SLASH);
    }

    rv = gfmSprite_update(pGlobal->pPlayer, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmQuadtree_collideSprite(pGlobal->pQt, pGlobal->pPlayer);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    if (pGlobal->playerAnim == PRINCE_SLASH &&
            gfmSprite_didAnimationFinish(pGlobal->pPlayer) == GFMRV_TRUE) {
        pGlobal->playerAnim = -1;
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_postUpdate() {
    gfmRV rv;
    double vx;

    rv = gfmSprite_getHorizontalVelocity(&vx, pGlobal->pPlayer);
    ASSERT(rv == GFMRV_OK, rv);

    if (pGlobal->playerAnim == PRINCE_SLASH ||
            pGlobal->playerAnim == PRINCE_HURT) {
        /*Ignore switching*/
    }
    else if (vx != 0) {
        PLAY(PRINCE_WALK);
    }
    else {
        PLAY(PRINCE_STAND);
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_draw() {
    gfmRV rv;

    rv = gfmSprite_draw(pGlobal->pPlayer, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

