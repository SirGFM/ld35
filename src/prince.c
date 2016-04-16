
#include <base/game_const.h>
#include <base/game_ctx.h>
#include <base/collision.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmGroup.h>
#include <GFraMe/gfmSprite.h>

#include <jam/prince.h>
#include <jam/type.h>

static gfmRV spawn_slash() {
    gfmSprite *pSlash;
    gfmGroupNode *pChild;
    gfmRV rv;
    int x, y, flip, type;

    rv = gfmSprite_getPosition(&x, &y, pGlobal->pPlayer);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_getDirection(&flip, pGlobal->pPlayer);
    ASSERT(rv == GFMRV_OK, rv);

    pSlash = 0;
    rv = gfmGroup_recycle(&pSlash, pGlobal->pHitbox);
    ASSERT(rv == GFMRV_OK, rv);
    pChild = 0;
    rv = gfmSprite_getChild((void**)&pChild, &type, pSlash);
    ASSERT(rv == GFMRV_OK, rv);

    if (flip) {
        x += PRINCE_SLASH_LOFFX;
    }
    else {
        x += PRINCE_SLASH_ROFFX;
    }
    y += PRINCE_SLASH_OFFY;

    rv = gfmSprite_init(pSlash, x, y, SLASH_W, SLASH_H, SLASH_SSET,
            SLASH_OFFX, SLASH_OFFY, pChild, T_SLASH);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setFrame(pSlash, 3);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_init() {
    gfmRV rv;

    rv = gfmSprite_init(pGlobal->pPlayer, 16/*x*/, PRT_FLOOR_Y - 8 /*y*/,
            8/*w*/, 8/*h*/, pGfx->pSset8x8, 0/*offx*/, 0/*offy*/, 0/*child*/,
            T_PRINCE);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_setFrame(pGlobal->pPlayer, PRT_PRINCE_FRAME);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_update() {
    gfmRV rv;

    if (pButton->left.state & gfmInput_pressed) {
        rv = gfmSprite_setHorizontalVelocity(pGlobal->pPlayer, -PRINCE_VX);
        ASSERT(rv == GFMRV_OK, rv);
        rv = gfmSprite_setDirection(pGlobal->pPlayer, 1);
        ASSERT(rv == GFMRV_OK, rv);
    }
    else if (pButton->right.state & gfmInput_pressed) {
        rv = gfmSprite_setHorizontalVelocity(pGlobal->pPlayer, PRINCE_VX);
        ASSERT(rv == GFMRV_OK, rv);
        rv = gfmSprite_setDirection(pGlobal->pPlayer, 0);
        ASSERT(rv == GFMRV_OK, rv);
    }
    else {
        rv = gfmSprite_setHorizontalVelocity(pGlobal->pPlayer, 0);
        ASSERT(rv == GFMRV_OK, rv);
    }

    if ((pButton->act.state & gfmInput_justPressed) == gfmInput_justPressed) {
        rv = spawn_slash();
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = gfmSprite_update(pGlobal->pPlayer, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmQuadtree_collideSprite(pGlobal->pQt, pGlobal->pPlayer);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV prince_draw() {
    gfmRV rv;

    /* TODO Change anim */

    rv = gfmSprite_draw(pGlobal->pPlayer, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

