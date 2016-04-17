
#include <base/game_const.h>
#include <base/game_ctx.h>

#include <jam/fairy.h>
#include <jam/type.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmSprite.h>

static int fairy_data[] = {
/*             len|fps|loop|data ... */
/*FAIRY_STAND*/ 4 , 8 , 1  , 48,49,50,51
};
static int fairy_data_len = sizeof(fairy_data) / sizeof(int);

gfmRV fairy_init() {
    gfmRV rv;

    rv = gfmSprite_init(pGlobal->pFairy, FAIRY_X, FAIRY_Y, FAIRY_W,
            FAIRY_H, FAIRY_SSET, FAIRY_OFFX, FAIRY_OFFY, 0/*child*/, T_MINION);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_addAnimations(pGlobal->pFairy, fairy_data,
            fairy_data_len);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_playAnimation(pGlobal->pFairy, 0);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_resetAnimation(pGlobal->pFairy);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV fairy_update() {
    gfmRV rv;

    rv = gfmSprite_update(pGlobal->pFairy, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV fairy_draw() {
    gfmRV rv;

    rv = gfmSprite_setDirection(pGlobal->pFairy, 0);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setHorizontalPosition(pGlobal->pFairy, FAIRY_X);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_draw(pGlobal->pFairy, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setDirection(pGlobal->pFairy, 1);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setHorizontalPosition(pGlobal->pFairy, FAIRY_X + FAIRY_W);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_draw(pGlobal->pFairy, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

