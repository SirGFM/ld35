/**
 * @file include/base/config.h
 *
 * Load, save and restores the previous configuration
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <GFraMe/gfmError.h>

/**
 * Loads the configuration. If the game failed to launch due to modifications on
 * the configurations, the last valid configuration is loaded.
 * Also, if it's the first time launching the game, the default configurations
 * are saved and loaded to RAM
 *
 * @return GFraMe return value
 */
gfmRV config_load();

/**
 * Loads the default configuration into RAM
 *
 * @return GFraMe return value
 */
void config_loadDefault();

/**
 * Save the current configuration but don't override the previous valid one
 *
 * @return GFraMe return value
 */
gfmRV config_saveModifications();

/**
 * Save the current configuration as a valid one
 *
 * @return GFraMe return value
 */
gfmRV config_saveCurAsValid();

/**
 * Save that an error happened, so that the previous valid configurations may
 * be loaded on the next launch
 *
 * @return GFraMe return value
 */
gfmRV config_saveError();

#endif /* __CONFIG_H__ */

