
#include <base/game_ctx.h>
#include <base/game_const.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmGroup.h>
#include <GFraMe/gfmSprite.h>

#include <jam/type.h>
#include <jam/slash.h>

static int slash_data[] = {18,19,20,21};

gfmRV spawn_slash(int x, int y, int flip) {
    gfmSprite *pSlash;
    gfmGroupNode *pChild;
    gfmRV rv;
    int index, type;

    pSlash = 0;
    rv = gfmGroup_recycle(&pSlash, pGlobal->pHitbox);
    ASSERT(rv == GFMRV_OK, rv);
    pChild = 0;
    rv = gfmSprite_getChild((void**)&pChild, &type, pSlash);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_init(pSlash, x, y, SLASH_W, SLASH_H, SLASH_SSET,
            SLASH_OFFX, SLASH_OFFY, pChild, T_SLASH);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSprite_addAnimation(&index, pSlash, slash_data, 4, 12, 0);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_playAnimation(pSlash, index);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_playAnimation(pSlash, index);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_resetAnimation(pSlash);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setDirection(pSlash, flip);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

