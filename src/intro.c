
#include <base/game_const.h>
#include <base/game_ctx.h>
#include <base/collision.h>
#include <base/state.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmSprite.h>

#include <jam/fairy.h>
#include <jam/prince.h>
#include <jam/type.h>
#include <jam/minion.h>

static char *pDictNames[] = {
    "floor"
};
static int pDictTypes[] = {
    T_FLOOR
};
static int dictLen = sizeof(pDictTypes) / sizeof(int);

gfmRV intro_init() {
    gfmSprite *pFloor;
    gfmRV rv;
    int x, y, w, h;

    rv = gfm_setBackground(pGame->pCtx, INTRO_BGCOLOR);
    ASSERT(rv == GFMRV_OK, rv);
    rv = fairy_init();
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmTilemap_init(pGlobal->pTilemap, pGfx->pSset16x16, 20/*w*/, 15/*h*/,
            -1/*defTile*/);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmTilemap_loadf(pGlobal->pTilemap, pGame->pCtx, INTRO_TILEMAP,
            sizeof(INTRO_TILEMAP), pDictNames, pDictTypes, dictLen);
    ASSERT(rv == GFMRV_OK, rv);

    rv = prince_init();
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_killAll(pGlobal->pFloor);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_killAll(pGlobal->pHitbox);
    ASSERT(rv == GFMRV_OK, rv);
    gfmGenArr_reset(pGlobal->pMinion);

    pFloor = 0;
    x = 0;
    y = V_HEIGHT - 32;
    w = V_WIDTH;
    h = 16;
    rv = gfmGroup_recycle(&pFloor, pGlobal->pFloor);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_init(pFloor, x, y, w, h, pGfx->pSset8x8, 0/*offx*/,
            0/*offy*/, 0/*child*/, T_FLOOR);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setFixed(pFloor);
    ASSERT(rv == GFMRV_OK, rv);

    pFloor = 0;
    x = V_WIDTH;
    y = 0;
    w = 8;
    h = V_HEIGHT;
    rv = gfmGroup_recycle(&pFloor, pGlobal->pFloor);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_init(pFloor, x, y, w, h, pGfx->pSset8x8, 0/*offx*/,
            0/*offy*/, 0/*child*/, T_FLOOR);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setFixed(pFloor);
    ASSERT(rv == GFMRV_OK, rv);

    pFloor = 0;
    x = -8;
    y = 0;
    w = 8;
    h = V_HEIGHT;
    rv = gfmGroup_recycle(&pFloor, pGlobal->pFloor);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_init(pFloor, x, y, w, h, pGfx->pSset8x8, 0/*offx*/,
            0/*offy*/, 0/*child*/, T_FLOOR);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_setFixed(pFloor);
    ASSERT(rv == GFMRV_OK, rv);

    PLAY_SONG(song_intro, 0.6);

    pGlobal->globalTimer = 0;
    pGlobal->globalCounter = 0;

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV intro_update() {
    gfmRV rv;

    rv = gfmQuadtree_initRoot(pGlobal->pQt, -8/*x*/, -8/*y*/, V_WIDTH+16,
            V_HEIGHT+16, QT_MAX_DEPTH, QT_MAX_NODES);
    ASSERT(rv == GFMRV_OK, rv);

    /* ---- spawn minions --------------------------------------------------- */

    if (pGlobal->globalTimer <= 0) {
        int x, rng, dir;

        pGlobal->globalCounter++;
        pGlobal->globalTimer += MINION_BASESPAWNTIME;
        rng = RNG(MINION_MINSPAWNTIME, MINION_MAXSPAWNTIME,
                MINION_MODSPAWNTIME);
        if (pGlobal->globalCounter > 8) {
            rng *= 8.0 / pGlobal->globalCounter;
        }
        pGlobal->globalTimer += rng;

        if (pGlobal->globalCounter % 2 == 0) {
            x = MINION_LX;
            dir = 0;
        }
        else {
            x = MINION_RX;
            dir = 1;
        }

        rv = minion_spawn(x, MINION_Y, dir);
        ASSERT(rv == GFMRV_OK, rv);
    }
    else {
        pGlobal->globalTimer -= pGame->elapsed;
    }

    /* ---- update ---------------------------------------------------------- */

    rv = gfmTilemap_update(pGlobal->pTilemap, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = fairy_update();
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_update(pGlobal->pFloor, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmQuadtree_collideGroup(pGlobal->pQt, pGlobal->pFloor);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    rv = minion_updateAll();
    ASSERT(rv == GFMRV_OK, rv);
    rv = prince_update();
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_update(pGlobal->pHitbox, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmQuadtree_collideGroup(pGlobal->pQt, pGlobal->pHitbox);
    if (rv == GFMRV_QUADTREE_OVERLAPED) {
        rv = collision_run();
        ASSERT(rv == GFMRV_OK, rv);
    }

    /* ---- post-update ----------------------------------------------------- */

    rv = minion_postUpdateAll();
    ASSERT(rv == GFMRV_OK, rv);
    rv = prince_postUpdate();
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV intro_draw() {
    gfmRV rv;

    rv = gfmTilemap_draw(pGlobal->pTilemap, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = minion_drawAll();
    ASSERT(rv == GFMRV_OK, rv);
    rv = prince_draw();
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_draw(pGlobal->pHitbox, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = fairy_draw();
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

