
#include <base/game_const.h>
#include <base/game_ctx.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmGenericArray.h>
#include <GFraMe/gfmSprite.h>

#include <stdlib.h>
#include <string.h>

struct stMinion {
    gfmSprite *pSelf;
    int time;
    int anim;
};

static gfmRV minion_getNew(minion **ppMinion) {
    minion *pMinion;
    gfmRV rv;

    pMinion = (minion*)malloc(sizeof(minion));
    ASSERT(pMinion, GFMRV_ALLOC_FAILED);
    memset(pMinion, 0x0, sizeof(minion));

    *ppMinion = pMinion;
    rv = GFMRV_OK;
__ret:
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

gfmRV minion_spawn(int x, int y, int dir) {
    minion *pMinion;
    gfmRV rv;

    gfmGenArr_getNextRef(minion, pGlobal->pMinion, 1/*inc*/, pMinion,
            minion_getNew);

    //rv = gfmSprite_init(pMinion->pSelf, 

    gfmGenArr_push(pGlobal->pMinion);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV minion_updateAll();
gfmRV minion_postUpdateAll();
gfmRV minion_drawAll();

