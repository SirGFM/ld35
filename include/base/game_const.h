/**
 * @file include/base/game_const.h
 *
 * Defines all constants
 */
#ifndef __GAME_CONST_H__
#define __GAME_CONST_H__

#include <GFraMe/core/gfmAudio_bkend.h>

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

#endif /* __GAME_CONST_H__ */

