/**
 * @file src/assets.c
 *
 * Handles loading assets and creating the required spritesets
 */
#include <base/game_const.h>
#include <base/game_ctx.h>

#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gframe.h>

/**
 * Load all assets
 *
 * @return GFraMe return value
 */
gfmRV assets_load() {
    /** Return value */
    gfmRV rv;

    /* Macros for loading stuff... */
#define GEN_SPRITESET(W, H) \
    rv = gfm_createSpritesetCached(&(pGfx->pSset##W##x##H), pGame->pCtx, \
            pGfx->texHandle, W, H); \
    ASSERT(rv == GFMRV_OK, rv)

#define LOAD_SFX(var, name) \
    rv = gfm_loadAudio(&(pAudio->var), pGame->pCtx, name, sizeof(name) - 1); \
    ASSERT(rv == GFMRV_OK, rv)

    rv = gfm_loadTextureStatic(&(pGfx->texHandle), pGame->pCtx, TEXATLAS,
            KEY_COLOR);
    ASSERT(rv == GFMRV_OK, rv);
    GEN_SPRITESET(8, 8);
    GEN_SPRITESET(16, 16);
    GEN_SPRITESET(64, 32);

    LOAD_SFX(minion_spawn, "sfx/minion_spawn.wav");
    LOAD_SFX(minion_atk, "sfx/minion_atk.wav");
    LOAD_SFX(minion_land, "sfx/minion_land.wav");
    LOAD_SFX(minion_hit, "sfx/minion_hit.wav");
    LOAD_SFX(prince_slash, "sfx/prince_slash.wav");
    LOAD_SFX(prince_hit, "sfx/prince_hit.wav");
    LOAD_SFX(prince_transform, "sfx/prince_transform.wav");
    LOAD_SFX(text, "sfx/text.wav");
    LOAD_SFX(song_menu, "mml/menu.mml");
    LOAD_SFX(song_bs, "mml/bs.mml");
    LOAD_SFX(song_intro, "mml/intro.mml");

    rv = GFMRV_OK;
__ret:
    return rv;
}

