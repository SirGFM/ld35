
#include <base/game_ctx.h>
#include <base/game_const.h>
#include <base/state.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>

gfmRV menu_init() {
    gfmRV rv;

    rv = gfm_setBackground(pGame->pCtx, BS_BGCOLOR);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmText_setTextStatic(pGlobal->pTitle, "A SIMPLE TALE",
            TEXT_COPY);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmText_setTextStatic(pGlobal->pStart, "PRESS SPACE TO START",
            TEXT_COPY);
    ASSERT(rv == GFMRV_OK, rv);

    PLAY_SONG(song_menu, 0.6);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV menu_update() {
    gfmRV rv;

    if ((pButton->act.state & gfmInput_justReleased) == gfmInput_justReleased) {
        pGame->nextState = ST_BACKSTORY;
    }

    rv = gfmText_update(pGlobal->pTitle, pGame->pCtx);
    rv = gfmText_update(pGlobal->pStart, pGame->pCtx);

    rv = GFMRV_OK;
    return rv;
}

gfmRV menu_draw() {
    gfmRV rv;

    rv = gfm_drawTile(pGame->pCtx, pGfx->pSset32x32, 0, V_HEIGHT - 32, 63, 0);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmText_draw(pGlobal->pTitle, pGame->pCtx);
    rv = gfmText_draw(pGlobal->pStart, pGame->pCtx);

    rv = GFMRV_OK;
__ret:
    return rv;
}

