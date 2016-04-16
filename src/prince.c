
#include <base/game_const.h>
#include <base/game_ctx.h>
#include <base/collision.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmSprite.h>

#include <jam/prince.h>
#include <jam/type.h>

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

    rv = gfmSprite_draw(pGlobal->pPlayer, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

