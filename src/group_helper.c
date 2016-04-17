
#include <base/game_ctx.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmGroup.h>
#include <GFraMe/gfmSprite.h>

#include <jam/group_helper.h>

gfmRV gh_initInf(gfmGroup *pGrp, int num, int dieOff) {
    return gh_init(pGrp, num, -1/*time*/, dieOff);
}

gfmRV gh_init(gfmGroup *pGrp, int num, int time, int dieOff) {
    gfmRV rv;

    rv = gfmGroup_setDefSpriteset(pGrp, pGfx->pSset8x8);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_setDefDimensions(pGrp, 8/*w*/, 8/*h*/, 0/*offX*/, 0/*offy*/);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_setDeathOnLeave(pGrp, dieOff);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_setDeathOnTime(pGrp, time);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_preCache(pGrp, num, num);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_setDrawOrder(pGrp, gfmDrawOrder_linear);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_setCollisionQuality(pGrp, gfmCollisionQuality_visibleOnly);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

