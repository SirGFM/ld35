
#include <base/game_const.h>
#include <base/game_ctx.h>

#include <GFraMe/gframe.h>
#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>

#include <jam/outro.h>

gfmRV ot_init() {
    gfmRV rv;

    pGlobal->globalCounter = 5;

    rv = gfm_setBackground(pGame->pCtx, BS_BGCOLOR);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmText_setTextStatic(pGlobal->pText,
            "THE EVIL FAIRY TURNED THE PRINCE INTO A BEAST. THE SPELL WOULD "
            "ONLY BE BROKEN WERE HE TO FIND TRUE LOVE. BUT THAT'S A STORY FOR "
            "ANOTHER DAY...", TEXT_COPY);
    ASSERT(rv == GFMRV_OK, rv);

    PLAY_SONG(song_bs, 0.6);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV ot_update() {
    gfmRV rv;

    if (gfmText_didFinish(pGlobal->pText) == GFMRV_TRUE) {
        if ((pButton->act.state & gfmInput_justReleased) == gfmInput_justReleased) {
            pGame->nextState = ST_MENU;
        }
    } /* if (gfmText_didFinish(pGlobal->pText) == GFMRV_TRUE) */
    else {
        if ((pButton->act.state & gfmInput_justReleased) == gfmInput_justReleased) {
            rv = gfmText_forceFinish(pGlobal->pText);
            ASSERT(rv == GFMRV_OK, rv);
        }

        rv = gfmText_update(pGlobal->pText, pGame->pCtx);
        ASSERT(rv == GFMRV_OK, rv);

#if 0
        do {
            char c;

            if (gfmText_getJustRendered(&c, pGlobal->pText) == GFMRV_OK) {
                PLAY_SFX(text, 0.3);
            }
        } while (0);
#endif
    }

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV ot_draw() {
    gfmRV rv;

    rv = gfm_drawTile(pGame->pCtx, BS_IMG_SSET, BS_IMG_X, BS_IMG_Y,
            BS_IMG_FIRST + pGlobal->globalCounter, BS_IMG_FLIP);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmText_draw(pGlobal->pText, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmText_draw(pGlobal->pQuickText, pGame->pCtx);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

