
#include <base/game_const.h>
#include <base/game_ctx.h>

#include <GFraMe/gframe.h>
#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>

#include <jam/backstory.h>

gfmRV bs_init() {
    gfmRV rv;

    pGlobal->globalCounter = -1;

    rv = gfm_setBackground(pGame->pCtx, BS_BGCOLOR);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmText_setTextStatic(pGlobal->pText, "dummy!", TEXT_COPY);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmText_forceFinish(pGlobal->pText);
    ASSERT(rv == GFMRV_OK, rv);

    PLAY_SONG(song_bs, 0.6);

    rv = GFMRV_OK;
__ret:
    return rv;
}

gfmRV bs_update() {
    gfmRV rv;

    if (gfmText_didFinish(pGlobal->pText) == GFMRV_TRUE) {
        char *pText;
        int len, doSwitch;

        doSwitch = 0;
        if (pGlobal->globalCounter == -1) {
            pGlobal->globalCounter++;
            doSwitch = 1;
        }
        else if ((pButton->act.state & gfmInput_justReleased) ==
                gfmInput_justReleased) {
            pGlobal->globalCounter++;
            doSwitch = 1;
        }

#define CASE(num, txt) case num: do { pText = txt; len = sizeof(txt) - 1; } while (0); break;
        switch (pGlobal->globalCounter) {
            CASE(0, "THIS IS A SIMPLE TALE");
            CASE(1, "AFTER COMING BACK FROM A TRIP, A PRINCE FOUND HIS CASTLE "
                    "BRIMMING WITH MINDLESS BEASTS");
            CASE(2, "HE DID AS HE WAS TAUGHT AND SLAYED EACH CREATURE");
            CASE(3, "AS HE FINISHED OFF THE LAST ONE, A FAIRY APPEARED AND "
                    "OFFERED TO GRANT HIM A WISH, SINCE THE CREATURES WERE "
                    "IMPRISIONING HER");
            CASE(4, "HE DIDN'T FEEL ANY TRUST IN THE FAIRY AND DECLINED HER "
                    "OFFER. AS HE DID THAT, MORE CREATURES APPEARED AND THE "
                    "FAIRY SAY THAT IF HE WEREN'T GOING TO HELP FROM GOOD "
                    "WILL, SHE WOULD HAVE IT HER WAY AND FORCE HIM TO DO AS "
                    "SHE WANTED");
            default: {
                pGame->nextState = ST_INTRO;
                return GFMRV_OK;
            }
        }

        if (doSwitch) {
            rv = gfmText_setText(pGlobal->pText, pText, len, TEXT_COPY);
            ASSERT(rv == GFMRV_OK, rv);
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

gfmRV bs_draw() {
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

