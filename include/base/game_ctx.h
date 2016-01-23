/**
 * @file include/base/game_ctx.h
 *
 * Defines all 'global' structs
 */
#ifndef __GAME_CTX_H__
#define __GAME_CTX_H__

#include <GFraMe/gframe.h>
#include <GFraMe/gfmInput.h>
#include <GFraMe/gfmQuadtree.h>
#include <GFraMe/gfmSpriteset.h>
#include <GFraMe/core/gfmAudio_bkend.h>

/* == Types declaration ===================================================== */

typedef struct stGameCtx gameCtx;
typedef struct stGfxCtx gfxCtx;
typedef struct stAudioCtx audioCtx;
typedef struct stButton button;
typedef struct stButtonCtx buttonCtx;
typedef struct stLastConfigCtx lastConfigCtx;
typedef struct stConfigCtx configCtx;
typedef struct stGlobalCtx globalCtx;

/* == Aligned size of structs =============================================== */

/** Calculate the size of a given type plus some padding to keep it aligned to
 * the architecture's word */
#define ALIGNED_SIZEOF(type) (sizeof(type) + (sizeof(type) % ALIGN))

/** Offset a memory position by some bytes */
#define OFFSET_MEM(mem, offset) (((char*)mem) + offset)

/** Define all basic struct sizes aligned to the arch's word */
#define SIZEOF_GAMECTX ALIGNED_SIZEOF(gameCtx)
#define SIZEOF_GFXCTX ALIGNED_SIZEOF(gfxCtx)
#define SIZEOF_AUDIOCTX ALIGNED_SIZEOF(audioCtx)
#define SIZEOF_BUTTONCTX ALIGNED_SIZEOF(buttonCtx)
#define SIZEOF_LASTCONFIGCTX ALIGNED_SIZEOF(lastConfigCtx)
#define SIZEOF_CONFIGCTX ALIGNED_SIZEOF(configCtx)
#define SIZEOF_GLOBALCTX ALIGNED_SIZEOF(globalCtx)

/** Calculate the size of the complete game buffer (so everything is
 * contiguously alloc'ed) */
#define SIZEOF_GAME_MEM (SIZEOF_GAMECTX + SIZEOF_GFXCTX + SIZEOF_AUDIOCTX + \
        SIZEOF_BUTTONCTX + SIZEOF_LASTCONFIGCTX + SIZEOF_CONFIGCTX + \
        SIZEOF_GLOBALCTX)

/** Define the offsets to each of the structs */
#define GAME_OFFSET         0
#define GFX_OFFSET          (GAME_OFFSET         + SIZEOF_GAMECTX)
#define AUDIO_OFFSET        (GFX_OFFSET          + SIZEOF_GFXCTX)
#define BUTTON_OFFSET       (AUDIO_OFFSET        + SIZEOF_AUDIOCTX)
#define CONFIG_OFFSET       (BUTTON_OFFSET       + SIZEOF_BUTTONCTX)
#define LASTCONFIG_OFFSET   (CONFIG_OFFSET       + SIZEOF_CONFIGCTX)
#define GLOBAL_OFFSET       (LASTCONFIG_OFFSET   + SIZEOF_LASTCONFIGCTX)

/* == Global context declaration ============================================ */

extern gameCtx *pGame;
extern gfxCtx *pGfx;
extern audioCtx *pAudio;
extern buttonCtx *pButton;
extern configCtx *pConfig;
extern globalCtx *pGlobal;

/* == Types definition ====================================================== */

/** Generic game flags */
enum enGameFlags {
    /** Set if the game is running in fullscreen mode */
    CFG_FULLSCREEN = 0x00000001,
    /** Set if VSync is enabled */
    CFG_VSYNC      = 0x00000010,
    /** Set if speedrun mode is enabled */
    CFG_SPEEDRUN   = 0x00000100,
    /** Set if the OpenGL 3.1 backend should be used */
    CFG_OPENGL3    = 0x00001000,
    /** Set if any error happened due to configurations */
    CFG_CONF_ERR   = 0x00010000,
    /** Set if developer mode is enabled */
    GAME_DEVMODE   = 0x00000002,
    /** Signal that the game loop should update only once and stop until it's
     * signaled again */
    GAME_STEP      = 0x00000020,
    /** Signal that 1 frame should be skipped (i.e., updated without
     * rendering) */
    GAME_SKIP_1    = 0x00000200,
    /** Signal that 2 frames should be skipped (i.e., updated without
     * rendering) */
    GAME_SKIP_2    = 0x00002000,
    /** Overrides 'GAME_STEP' and force the game loop to run normally */
    GAME_RUN       = 0x00020000
};
typedef enum enGameFlags gameFlags;

/** Store data related to game */
struct stGameCtx {
    /** The framework's context */
    gfmCtx *pCtx;
    /** Currently running state (e.g., ST_PLAYSTATE) */
    int curState;
    /** If different from 'ST_NONE', the state to which the game must switch on
     * the end of this frame */
    int nextState;
};

/** Store all handles to texture and spritesets' pointers */
struct stGfxCtx {
    /** 8x8 spriteset of the main texture */
    gfmSpriteset *pSset8x8;
    /** Handle of the main texture atlas */
    int texHandle;
};

/** Store all handles to songs and sound effects */
struct stAudioCtx {
    /* TODO Add any song/sfx here */
};

/** Simple button definition, so it's easier to update and access each button */
struct stButton {
    /** Button handle, internal to the framework */
    int handle;
    /** Number of times the button was consecutivelly pressed */
    int numPressed;
    /** Current state of the button */
    gfmInputState state;
    /** Ignore; Used to expand the struct to 32 bytes */
    int padding;
};

/** Store all actions do-able ingame */
struct stButtonCtx {
    /** Button to switch between fullscreen and windowed mode */
    button fullscreen;
    /* TODO Add buttons */
};

/** Store the configurations on the last successfull launch of the game */
struct stLastConfigCtx {
    /** Binary flags for the game (e.g., whether it's in fullscreen mode); Check
     * 'enum enGameFlags' documentation */
    gameFlags flags;
    /** Current resolution, if in fullscreen mode */
    int resolution;
    /** Window's width (inside which the virtual buffer is resized and
     * letter-boxed) */
    int width;
    /** Window's height (inside which the virtual buffer is resized and
     * letter-boxed) */
    int height;
    /** How many frames should be updated and rendered per second */
    int fps;
    /** Audio quality (frequency, bits per samples and number of channels) */
    gfmAudioQuality audioQuality;
    /* TODO Add button mapping */
};

/** Store all data modifiably on the option menu, as well as anything that may
 * be saved on the config file */
struct stConfigCtx {
    /** Store the previous configurations so it can be restored on error */
    lastConfigCtx *pLast;
    /** Binary flags for the game (e.g., whether it's in fullscreen mode); Check
     * 'enum enGameFlags' documentation */
    gameFlags flags;
    /** Current resolution, if in fullscreen mode */
    int curResolution;
    /** Window's width (inside which the virtual buffer is resized and
     * letter-boxed) */
    int width;
    /** Window's height (inside which the virtual buffer is resized and
     * letter-boxed) */
    int height;
    /** How many frames should be updated and rendered per second */
    int fps;
    /** Audio quality (frequency, bits per samples and number of channels) */
    gfmAudioQuality audioQuality;
    /* TODO Add button mapping */
};

/** Store game-related variables that should be globally accessible */
struct stGlobalCtx {
    /** The quadtree for collision */
    gfmQuadtreeRoot *pQt;
    /* TODO Add any other globally accessible variable (e.g., a tilemap) */
};

#endif /* __GAME_CTX_H__ */
