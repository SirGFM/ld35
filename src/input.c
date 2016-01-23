/**
 * @file src/input.c
 *
 * Updates the game input and runs commands whenever an action is detected
 * (e.g., switch to/from fullscreen on btFullscreen)
 */
#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmInput.h>

#include <base/game_ctx.h>
#include <base/input.h>

/**
 * Update all buttons' states
 *
 * @return GFraMe return value
 */
gfmRV input_updateButtons() {
    /** List of buttons, used to easily iterate through all of pButton's
     * members */
    button *pButtonList;
    /** Return value */
    gfmRV rv;
    /** Index of the current button being iterated */
    int i;

    /* Iterate through all buttons and retrieve their state */
    i = 0;
    pButtonList = (button*)pButton;
    while (i < (sizeof(buttonCtx) / sizeof(button))) {
        rv = gfm_getKeyState(&(pButtonList[i].state),
                &(pButtonList[i].numPressed), pGame->pCtx,
                pButtonList[i].handle);
        ASSERT(rv == GFMRV_OK, rv);

        i++;
    }

    /* Switch to/from fullscreen if the key was just pressed */
    if ((pButton->fullscreen.state & gfmInput_justReleased) ==
            gfmInput_justReleased) {
        if (pConfig->flags & CFG_FULLSCREEN) {
            rv = gfm_setWindowed(pGame->pCtx);
            ASSERT(rv == GFMRV_OK, rv);
            pConfig->flags ^= CFG_FULLSCREEN;
        }
        else {
            rv = gfm_setFullscreen(pGame->pCtx);
            ASSERT(rv == GFMRV_OK, rv);
            pConfig->flags |= CFG_FULLSCREEN;
        }
        /* TODO Save the new state of the game's window */
    }

    /* TODO Add actions that should be triggered as soon as key are pressed */

    rv = GFMRV_OK;
__ret:
    return rv;
}

/**
 * Initialize and bind all buttons
 *
 * @return GFraMe return value
 */
gfmRV input_init() {
    /** Return value */
    gfmRV rv;

    /* Initialize all buttons */
#define ADD_KEY(bt) \
    rv = gfm_addVirtualKey(&(pButton->bt.handle), pGame->pCtx); \
    ASSERT(rv == GFMRV_OK, rv)

    ADD_KEY(fullscreen);
    /* TODO Add other keys */

#undef ADD_KEY

    /* Bind all keys */
#define BIND_KEY(bt, key) \
    rv = gfm_bindInput(pGame->pCtx, pButton->bt.handle, key); \
    ASSERT(rv == GFMRV_OK, rv)
#define BIND_GAMEPAD_BT(bt, key, port) \
    rv = gfm_bindGamepadInput(pGame->pCtx, pButton->bt.handle, key, port); \
    ASSERT(rv == GFMRV_OK, rv)

    BIND_KEY(fullscreen, gfmKey_f12);
    /* TODO Bind other keys */

#undef BIND_KEY

    rv = GFMRV_OK;
__ret:
    return rv;
}

