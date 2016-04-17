
#include <base/collision.h>
#include <base/game_const.h>
#include <base/game_ctx.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmGenericArray.h>
#include <GFraMe/gfmSprite.h>

#include <jam/type.h>

#include <stdlib.h>
#include <string.h>

enum {
    MINION_STAND,
    MINION_ATK,
    MINION_HURT
};

static int minion_data[] = {
/*              len|fps|loop|data ... */
/*MINION_STAND*/ 1 , 0 , 0  , 64,
/*MINION_ATK  */ 1 , 0 , 0  , 64,
/*MINION_HURT */ 3 , 4 , 0  , 64,65,64
};
static int minion_data_len = sizeof(minion_data) / sizeof(int);

#define PLAY(animation) \
  do { \
    if (pMinion->anim != animation) { \
      rv = gfmSprite_playAnimation(pMinion->pSelf, animation); \
      ASSERT(rv == GFMRV_OK, rv); \
      pMinion->anim = animation; \
    } \
  } while(0)

struct stMinion {
    gfmSprite *pSelf;
    int time;
    int anim;
    int sign;
};

gfmRV minion_isAlive(minion *pMinion) {
    if (pMinion->anim == MINION_HURT) {
        return GFMRV_FALSE;
    }
    return GFMRV_TRUE;
}

gfmRV minion_hurt(minion *pMinion) {
    gfmRV rv;

    if (pMinion->anim == MINION_HURT) {
        return GFMRV_OK;
    }

    PLAY(MINION_HURT);
    rv = gfmSprite_setHorizontalVelocity(pMinion->pSelf, 0);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV minion_revert(minion *pMinion) {
    gfmRV rv;

    pMinion->sign *= -1;
    rv = gfmSprite_setDirection(pMinion->pSelf, (pMinion->sign < 0));
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

static gfmRV minion_getNew(minion **ppMinion) {
    minion *pMinion;
    gfmRV rv;

    pMinion = (minion*)malloc(sizeof(minion));
    ASSERT(pMinion, GFMRV_ALLOC_FAILED);
    memset(pMinion, 0x0, sizeof(minion));
    rv = gfmSprite_getNew(&(pMinion->pSelf));
    ASSERT(rv == GFMRV_OK, rv);

    *ppMinion = pMinion;
    rv = GFMRV_OK;
__ret:
    if (rv != GFMRV_OK && pMinion) {
        free(pMinion);
    }

    return rv;
}

void minion_free(minion **ppMinion) {
    if (!ppMinion || !*ppMinion) {
        return;
    }

    gfmSprite_free(&((*ppMinion)->pSelf));
    free(*ppMinion);
    *ppMinion = 0;
}

gfmRV minion_spawn(int x, int y, int flip) {
    minion *pMinion;
    gfmRV rv;

    gfmGenArr_getNextRef(minion, pGlobal->pMinion, 1/*inc*/, pMinion,
            minion_getNew);

    rv = gfmSprite_init(pMinion->pSelf, x, y, MINION_W, MINION_H, MINION_SSET,
            MINION_OFFX, MINION_OFFY, pMinion, T_MINION);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_setVerticalAcceleration(pMinion->pSelf, GRAV);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_addAnimations(pMinion->pSelf, minion_data, minion_data_len);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_setDirection(pMinion->pSelf, flip);
    ASSERT(rv == GFMRV_OK, rv);
    if (flip) {
        pMinion->sign = -1;
    }
    else {
        pMinion->sign = 1;
    }

    pMinion->anim = -1;
    PLAY(MINION_STAND);

    pMinion->time = RNG(MINION_MINTIME, MINION_MAXTIME, MINION_MODTIME);

    gfmGenArr_push(pGlobal->pMinion);

    rv = GFMRV_OK;
__ret:
    return rv;
}

static gfmRV minion_update(minion *pMinion) {
    gfmRV rv;
    gfmCollision dir;

    if (pMinion->time  > 0) {
        pMinion->time -= pGame->elapsed;
    }
    rv = gfmSprite_getCollision(&dir, pMinion->pSelf);
    ASSERT(rv == GFMRV_OK, rv);

    if (pMinion->anim == MINION_HURT) {
        /* Ignore everything */
    }
    else if ((dir & gfmCollision_down) && pMinion->time <= 0) {
        pMinion->time += RNG(MINION_MINTIME, MINION_MAXTIME, MINION_MODTIME);
        rv = gfmSprite_setVelocity(pMinion->pSelf, pMinion->sign * MINION_VX,
                MINION_VY);
        ASSERT(rv == GFMRV_OK, rv);
    }
    else if (dir & gfmCollision_down) {
        rv = gfmSprite_setHorizontalVelocity(pMinion->pSelf, 0);
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = gfmSprite_update(pMinion->pSelf, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmQuadtree_collideSprite(pGlobal->pQt, pMinion->pSelf);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    if (pMinion->anim == MINION_HURT && 
            gfmSprite_didAnimationFinish(pMinion->pSelf) == GFMRV_TRUE) {
        rv = gfmSprite_setVerticalPosition(pMinion->pSelf, VERTICAL_OOB);
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}
gfmRV minion_updateAll() {
    gfmRV rv;
    int i;

    i = 0;
    while (i < gfmGenArr_getUsed(pGlobal->pMinion)) {
        rv = minion_update(gfmGenArr_getObject(pGlobal->pMinion, i));
        ASSERT(rv == GFMRV_OK, rv);
        i++;
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

static gfmRV minion_postUpdate(minion *pMinion) {
    gfmRV rv;
    double vx;

    rv = gfmSprite_getHorizontalVelocity(&vx, pMinion->pSelf);
    ASSERT(rv == GFMRV_OK, rv);

    if (pMinion->anim == MINION_HURT) {
        /*Ignore modifying*/
    }
    else if (vx != 0) {
        PLAY(MINION_ATK);
    }
    else {
        PLAY(MINION_STAND);
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}
gfmRV minion_postUpdateAll() {
    gfmRV rv;
    int i;

    i = 0;
    while (i < gfmGenArr_getUsed(pGlobal->pMinion)) {
        rv = minion_postUpdate(gfmGenArr_getObject(pGlobal->pMinion, i));
        ASSERT(rv == GFMRV_OK, rv);
        i++;
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

static gfmRV minion_draw(minion *pMinion) {
    gfmRV rv;

    rv = gfmSprite_draw(pMinion->pSelf, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}
gfmRV minion_drawAll() {
    gfmRV rv;
    int i;

    i = 0;
    while (i < gfmGenArr_getUsed(pGlobal->pMinion)) {
        rv = minion_draw(gfmGenArr_getObject(pGlobal->pMinion, i));
        ASSERT(rv == GFMRV_OK, rv);
        i++;
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

