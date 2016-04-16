
#include <base/game_const.h>
#include <base/game_ctx.h>
#include <base/collision.h>
#include <base/state.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmSprite.h>

#include <jam/prince.h>

gfmRV intro_init() {
    gfmRV rv;

    rv = prince_init();
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_killAll(pGlobal->pFloor);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_killAll(pGlobal->pHitbox);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV intro_update() {
    gfmRV rv;

    rv = gfmQuadtree_initRoot(pGlobal->pQt, -8/*x*/, -8/*y*/, V_WIDTH+16,
            V_HEIGHT+16, QT_MAX_DEPTH, QT_MAX_NODES);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_update(pGlobal->pFloor, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmQuadtree_collideGroup(pGlobal->pQt, pGlobal->pFloor);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = prince_update();
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_update(pGlobal->pHitbox, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmQuadtree_collideGroup(pGlobal->pQt, pGlobal->pHitbox);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV intro_draw() {
    gfmRV rv;

    rv = prince_draw();
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_draw(pGlobal->pHitbox, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

