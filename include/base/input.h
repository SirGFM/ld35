/**
 * @file include/base/input.h
 *
 * Updates the game input and runs commands whenever an action is detected
 * (e.g., switch to/from fullscreen on btFullscreen)
 */
#ifndef __INPUT_H__
#define __INPUT_H__

#include <GFraMe/gfmError.h>

/**
 * Update all buttons' states
 *
 * @return GFraMe return value
 */
gfmRV input_updateButtons();

#if defined(DEBUG)
/**
 * Update only the debug buttons
 *
 * @return GFraMe return value
 */
gfmRV input_updateDebugButtons();
#endif

/**
 * Initialize and bind all buttons
 *
 * @return GFraMe return value
 */
gfmRV input_init();

#endif /* __INPUT_H__ */

