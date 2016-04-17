/**
 * @file include/base/game_const.h
 *
 * Defines all constants
 */
#ifndef __GAME_CONST_H__
#define __GAME_CONST_H__

/* TODO Set attributes for the game */

/* == Game's basic configurations =========================================== */

/** Game's "organization" */
#define ORG         "organization"
/** Game's title */
#define TITLE       "base"
/** Config file name */
#define CONF        "config.sav"
/** Virtual window's width */
#define V_WIDTH     320
/** Virtual window's height */
#define V_HEIGHT    240
/** Whether the user can resize the game window */
#define CAN_RESIZE  1
/** Initial background color in 0xAARRGGBB format */
#define BG_COLOR    0xFF000000
/** Spriteset used by the FPS counter. It's ignored, if NULL */
#define FPS_SSET    pGfx->pSset8x8
/** First ASCII tile in FPS_SSET */
#define FPS_INIT    0
/** FPS counter position. It must be enabled through a 'gfm_showFPSCounter',
 * which is called by default on debug mode */
#define FPS_X       0
#define FPS_Y       0

/* == Config file IDs ======================================================= */

#define CONF_ID_INIT        "init"
#define CONF_ID_FLAGS       "flags"
#define CONF_ID_RES         "res"
#define CONF_ID_WIDTH       "width"
#define CONF_ID_HEIGHT      "height"
#define CONF_ID_FPS         "fps"
#define CONF_ID_AUDIOQ      "audio"
#define CONF_ID_LAST_FLAGS  "lFlags"
#define CONF_ID_LAST_RES    "lRes"
#define CONF_ID_LAST_WIDTH  "lWidth"
#define CONF_ID_LAST_HEIGHT "lHeight"
#define CONF_ID_LAST_FPS    "lFps"
#define CONF_ID_LAST_AUDIOQ "lAudio"

/* == Default configuration ================================================= */

#define CONF_FLAGS  (CFG_VSYNC)
#define CONF_RES    0
#define CONF_WIDTH  640
#define CONF_HEIGHT 480
#define CONF_FPS    60
#define CONF_AUDIOQ gfmAudio_defQuality

/* == ... =================================================================== */

/** Texture's transparent color */
#define KEY_COLOR       0xFF00FF
/** Maximum number of times the quadtree will subdivide */
#define QT_MAX_DEPTH    6
/** Number of nodes required for the quadtree to subdivide */
#define QT_MAX_NODES    10
#define TEXATLAS        "atlas.bmp"

/* == ... =================================================================== */

#define GRAV                500
#define VERTICAL_OOB        1000

#define PRT_FLOOR_Y         (V_HEIGHT - 32)
#define PRT_FLOOR_MAX       8
#define PRT_PRINCE_FRAME    (65)
#define PRT_HITBOX_MAX      100

#define PRINCE_X            (V_WIDTH / 2)
#define PRINCE_Y            (V_HEIGHT - 12 - 32)
#define PRINCE_W            4
#define PRINCE_H            12
#define PRINCE_OFFX         -6
#define PRINCE_OFFY         -4
#define PRINCE_SSET         pGfx->pSset16x16
#define PRINCE_SLASH_FRAME  35
#define PRINCE_VX           100
#define PRINCE_SLASH_ROFFX  15
#define PRINCE_SLASH_LOFFX  -15
#define PRINCE_SLASH_OFFY   -2

#define SLASH_W             6
#define SLASH_H             12
#define SLASH_SSET          pGfx->pSset16x16
#define SLASH_OFFX          -8
#define SLASH_OFFY          -4

#define MINION_W            12
#define MINION_H            8
#define MINION_SSET         pGfx->pSset16x16
#define MINION_OFFX         -4
#define MINION_OFFY         -8
#define MINION_MINTIME      0
#define MINION_MAXTIME      20
#define MINION_MODTIME      100
#define MINION_VX           96
#define MINION_VY           -100
#define MINION_Y            (V_HEIGHT - 96)
#define MINION_LX           16
#define MINION_RX           (V_WIDTH - MINION_W - 16)

#define MINION_BASESPAWNTIME 150
#define MINION_MINSPAWNTIME 10
#define MINION_MAXSPAWNTIME 50
#define MINION_MODSPAWNTIME 50

#define HITBOX_MAX_TIME     300

#define INTRO_BGCOLOR       0xff5b6ee1
#define INTRO_TILEMAP       "intro.gfm"

#define FAIRY_X             ((V_WIDTH - 16) / 2)
#define FAIRY_Y             64
#define FAIRY_W             16
#define FAIRY_H             16
#define FAIRY_SSET          pGfx->pSset16x16
#define FAIRY_OFFX          0
#define FAIRY_OFFY          0

#define BS_BGCOLOR          0xff000000

#define BS_IMG_X            ((V_WIDTH - 64) / 2)
#define BS_IMG_Y            ((V_HEIGHT - 32) / 2)
#define BS_IMG_SSET         pGfx->pSset64x32
#define BS_IMG_FIRST        16
#define BS_IMG_FLIP         0

#define TEXT_DELAY          60
#define TEXT_BINDMODE       0
#define TEXT_COPY           1

#define BS_QKTEXT_X         8
#define BS_QKTEXT_Y         8
#define BS_QKTEXT_W         ((V_WIDTH - 16) / 8)
#define BS_QKTEXT_LINES     1
#define BS_QKTEXT_TEXT      "-- PRESS SPACE TO COMPLETE/SKIP --"

#define BS_TEXT_X           8
#define BS_TEXT_Y           (BS_IMG_Y + 32 + 8)
#define BS_TEXT_W           ((V_WIDTH - 16) / 8)
#define BS_TEXT_LINES       ((V_HEIGHT - BS_TEXT_Y - 8) / 8)

#endif /* __GAME_CONST_H__ */

