/**
 * @file include/base/global.h
 *
 * Declare all global variables
 */
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <GFraMe/gfmError.h>

/**
 * Initialize all pointers
 *
 * @param  [ in]pMem A buffer of at least SIZEOF_GAME_MEM bytes
 */
void global_init(void *pMem);

/**
 * Initialize all variables in pGlobal
 *
 * @return GFraMe return value
 */
gfmRV global_initUserVar();

/**
 * Release all variables in pGlobal
 */
void global_freeUserVar();


#endif /* __GLOBAL_H__ */

