/**
 * @file src/config.c
 *
 * Load, save and restores the previous configuration
 */
#include <GFraMe/gfmAssert.h>
#include <GFraMe/gfmError.h>
#include <GFraMe/gfmSave.h>

#include <base/game_const.h>
#include <base/game_ctx.h>
#include <base/config.h>

/* TODO Add button mapping */

/**
 * Save the current configuration to the file
 */
static gfmRV config_saveCur(gfmSave *pSave) {
    /** Return value */
    gfmRV rv;

    rv = gfmSave_writeStatic(pSave, CONF_ID_FLAGS, pConfig->flags);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_RES, pConfig->curResolution);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_WIDTH, pConfig->width);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_HEIGHT, pConfig->height);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_FPS, pConfig->fps);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_AUDIOQ, pConfig->audioQuality);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

/**
 * Save the current "last valid configuration" to the file
 */
static gfmRV config_saveLastValid(gfmSave *pSave) {
    /** Return value */
    gfmRV rv;

    rv = gfmSave_writeStatic(pSave, CONF_ID_LAST_FLAGS, pConfig->pLast->flags);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_LAST_RES,
            pConfig->pLast->resolution);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_LAST_WIDTH, pConfig->pLast->width);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_LAST_HEIGHT,
            pConfig->pLast->height);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_LAST_FPS, pConfig->pLast->fps);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_writeStatic(pSave, CONF_ID_LAST_AUDIOQ,
            pConfig->pLast->audioQuality);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

/**
 * Save the default configuration into the file and load it into RAM
 *
 * @return GFraMe return value
 */
static gfmRV config_firstLoad(gfmSave *pSave) {
    /** Return value */
    gfmRV rv;

    /* Load all default configurations to RAM */
    config_loadDefault();
    pConfig->pLast->width = CONF_WIDTH;
    pConfig->height = CONF_HEIGHT;
    pConfig->pLast->height = CONF_HEIGHT;
    pConfig->fps = CONF_FPS;
    pConfig->pLast->fps = CONF_FPS;
    pConfig->pLast->audioQuality = CONF_AUDIOQ;

    /* Save it to the file */
    rv = config_saveCur(pSave);
    ASSERT(rv == GFMRV_OK, rv);
    rv = config_saveLastValid(pSave);
    ASSERT(rv == GFMRV_OK, rv);
    /* Save a token to indicate that the configuration was initialized */
    rv = gfmSave_writeStatic(pSave, CONF_ID_INIT, 1);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

/**
 * Load the current configuration into RAM
 *
 * @return GFraMe return value
 */
static gfmRV config_doLoad(gfmSave *pSave) {
    /** Return value */
    gfmRV rv;

    /* Load all configurations from the file */
    rv = gfmSave_readStatic((int*)&(pConfig->flags), pSave, CONF_ID_FLAGS);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->curResolution), pSave, CONF_ID_RES);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->width), pSave, CONF_ID_WIDTH);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->height), pSave, CONF_ID_HEIGHT);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->fps), pSave, CONF_ID_FPS);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic((int*)&(pConfig->audioQuality), pSave,
            CONF_ID_AUDIOQ);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic((int*)&(pConfig->pLast->flags), pSave,
            CONF_ID_LAST_FLAGS);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->pLast->resolution), pSave,
            CONF_ID_LAST_RES);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->pLast->width), pSave,
            CONF_ID_LAST_WIDTH);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->pLast->height), pSave,
            CONF_ID_LAST_HEIGHT);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic(&(pConfig->pLast->fps), pSave, CONF_ID_LAST_FPS);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_readStatic((int*)&(pConfig->pLast->audioQuality), pSave,
            CONF_ID_LAST_AUDIOQ);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    return rv;
}

/**
 * Loads the configuration. If the game failed to launch due to modifications on
 * the configurations, the last valid configuration is loaded.
 * Also, if it's the first time launching the game, the default configurations
 * are saved and loaded to RAM
 *
 * @return GFraMe return value
 */
gfmRV config_load() {
    /** Config file */
    gfmSave *pSave;
    /** Return value */
    gfmRV rv;

    /* Open the config file */
    pSave = 0;
    rv = gfmSave_getNew(&pSave);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_bindStatic(pSave, pGame->pCtx, CONF);
    ASSERT(rv == GFMRV_OK, rv);

    rv = gfmSave_findIdStatic(pSave, CONF_ID_INIT);
    if (rv == GFMRV_SAVE_ID_NOT_FOUND) {
        /* If CONF_INIT hasn't been writen, the config still needs to be
         * initialized */
        rv = config_firstLoad(pSave);
    }
    else {
        /* The game has already been configured before, load the
         * configurations */
        rv = config_doLoad(pSave);
    }
    ASSERT(rv == GFMRV_OK, rv);

    /* Check if an error happened on the previous launch and, if so, revert the
     * configurations */
    if (pConfig->flags & CFG_CONF_ERR) {
        pConfig->flags = pConfig->pLast->flags;
        pConfig->curResolution = pConfig->pLast->resolution;
        pConfig->width = pConfig->pLast->width;
        pConfig->height = pConfig->pLast->height;
        pConfig->fps = pConfig->pLast->fps;
        pConfig->audioQuality = pConfig->pLast->audioQuality;
    }

    rv = GFMRV_OK;
__ret:
    if (pSave) {
        gfmSave_free(&pSave);
    }

    return rv;
}

/**
 * Loads the default configuration into RAM
 *
 * @return GFraMe return value
 */
void config_loadDefault() {
    /* Simply load it */
    pConfig->flags = CONF_FLAGS;
    pConfig->pLast->flags = CONF_FLAGS;
    pConfig->curResolution = CONF_RES;
    pConfig->pLast->resolution = CONF_RES;
    pConfig->width = CONF_WIDTH;
    pConfig->audioQuality = CONF_AUDIOQ;
}

/**
 * Save the current configuration but don't override the previous valid one
 *
 * @return GFraMe return value
 */
gfmRV config_saveModifications() {
    /** Config file */
    gfmSave *pSave;
    /** Return value */
    gfmRV rv;

    /* Open the config file */
    pSave = 0;
    rv = gfmSave_getNew(&pSave);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_bindStatic(pSave, pGame->pCtx, CONF);
    ASSERT(rv == GFMRV_OK, rv);

    /* Save only the current configuration */
    rv = config_saveCur(pSave);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    if (pSave) {
        gfmSave_free(&pSave);
    }

    return rv;
}

/**
 * Save the current configuration as a valid one
 *
 * @return GFraMe return value
 */
gfmRV config_saveCurAsValid() {
    /** Config file */
    gfmSave *pSave;
    /** Return value */
    gfmRV rv;

    /* Open the config file */
    pSave = 0;
    rv = gfmSave_getNew(&pSave);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_bindStatic(pSave, pGame->pCtx, CONF);
    ASSERT(rv == GFMRV_OK, rv);

    /* Copy the current configuration to the valids ones */
    pConfig->pLast->flags = pConfig->flags;
    pConfig->pLast->resolution = pConfig->curResolution;
    pConfig->pLast->width = pConfig->width;
    pConfig->pLast->height = pConfig->height;
    pConfig->pLast->fps = pConfig->fps;
    pConfig->pLast->audioQuality = pConfig->audioQuality;
    /* Save it to the file */
    rv = config_saveLastValid(pSave);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    if (pSave) {
        gfmSave_free(&pSave);
    }

    return rv;
}

/**
 * Save that an error happened, so that the previous valid configurations may
 * be loaded on the next launch
 *
 * @return GFraMe return value
 */
gfmRV config_saveError() {
    /** Config file */
    gfmSave *pSave;
    /** Return value */
    gfmRV rv;

    /* Open the config file */
    pSave = 0;
    rv = gfmSave_getNew(&pSave);
    ASSERT(rv == GFMRV_OK, rv);
    rv = gfmSave_bindStatic(pSave, pGame->pCtx, CONF);
    ASSERT(rv == GFMRV_OK, rv);

    /* Set the error flag and save it */
    pConfig->flags |= CFG_CONF_ERR;
    rv = gfmSave_writeStatic(pSave, CONF_ID_FLAGS, pConfig->flags);
    ASSERT(rv == GFMRV_OK, rv);

    rv = GFMRV_OK;
__ret:
    if (pSave) {
        gfmSave_free(&pSave);
    }

    return rv;
}

