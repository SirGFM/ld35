/**
 * @file src/global.c
 *
 * Declare all global variables
 */
#include <base/game_ctx.h>
#include <base/game_const.h>
#include <base/global.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmSprite.h>
#include <GFraMe/gfmQuadtree.h>

#include <jam/group_helper.h>
#include <jam/minion.h>

/** Store data related to game */
gameCtx *pGame = 0;

/** Store all handles to texture and spritesets' pointers */
gfxCtx *pGfx = 0;

/** Store all handles to songs and sound effects */
audioCtx *pAudio = 0;

/** Store all actions do-able ingame */
buttonCtx *pButton = 0;

/** Store all data modifiably on the option menu, as well as anything that may
 * be saved on the config file */
configCtx *pConfig = 0;

/** Store game-related variables that should be globally accessible */
globalCtx *pGlobal = 0;

/**
 * Initialize all pointers
 *
 * @param  [ in]pMem A buffer of at least SIZEOF_GAME_MEM bytes
 */
void global_init(void *pMem) {
    /* Retrieve all pointers from the memory */
    pGame = (gameCtx*)OFFSET_MEM(pMem, GAME_OFFSET);
    pGfx = (gfxCtx*)OFFSET_MEM(pMem, GFX_OFFSET);
    pAudio = (audioCtx*)OFFSET_MEM(pMem, AUDIO_OFFSET);
    pButton = (buttonCtx*)OFFSET_MEM(pMem, BUTTON_OFFSET);
    pConfig = (configCtx*)OFFSET_MEM(pMem, CONFIG_OFFSET);
    pGlobal = (globalCtx*)OFFSET_MEM(pMem, GLOBAL_OFFSET);

    /* Set any pointers within those structs that were already alloc'ed */
    pConfig->pLast = (configCtx*)OFFSET_MEM(pMem, LASTCONFIG_OFFSET);
}

/**
 * Initialize all variables in pGlobal
 *
 * @return GFraMe return value
 */
gfmRV global_initUserVar() {
    /** GFraMe return value */
    gfmRV rv;

    /* Initialize the quadtree, so it can be later used for collision */
    rv = gfmQuadtree_getNew(&(pGlobal->pQt));
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmGroup_getNew(&(pGlobal->pFloor));
    ASSERT(rv == GFMRV_OK, rv);
    rv = gh_initInf(pGlobal->pFloor, PRT_FLOOR_MAX, 0/*dieOff*/);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_setCollisionQuality(pGlobal->pFloor,
            gfmCollisionQuality_collideEverything);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmGroup_getNew(&(pGlobal->pHitbox));
    ASSERT(rv == GFMRV_OK, rv);
    rv = gh_init(pGlobal->pHitbox, PRT_HITBOX_MAX, HITBOX_MAX_TIME, 1/*dieOff*/);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSprite_getNew(&(pGlobal->pPlayer));
    ASSERT(rv == GFMRV_OK, rv);

    /* TODO Initialize everything */

    rv = GFMRV_OK;
__ret:
    return rv;
}

/**
 * Release all variables in pGlobal
 */
void global_freeUserVar() {
    gfmGroup_free(&(pGlobal->pFloor));
    gfmGroup_free(&(pGlobal->pHitbox));
    gfmSprite_free(&(pGlobal->pPlayer));
    gfmQuadtree_free(&(pGlobal->pQt));
    gfmGenArr_clean(pGlobal->pMinion, minion_free);
}

