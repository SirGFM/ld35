/**
 * @file include/base/state.h
 *
 * List all the possibles states
 */
#ifndef __STATES_H__
#define __STATES_H__

/* TODO Add more states */
enum enState {
    ST_NONE = 0,
    ST_MENU,
    ST_BACKSTORY,
    ST_INTRO,
    ST_OUTRO,
    ST_PAUSE,
    ST_MAX,
};
typedef enum enState state;

#endif /* __STATES_H__ */

