
#ifndef __MINION_STRUCT__
#define __MINION_STRUCT__
typedef struct stMinion minion;
#endif /* __MINION_STRUCT__ */

#ifndef __MINION_H__
#define __MINION_H__

#include <GFraMe/gfmError.h>

void minion_free(minion **ppMinion);
gfmRV minion_spawn(int x, int y, int dir);
gfmRV minion_updateAll();
gfmRV minion_postUpdateAll();
gfmRV minion_drawAll();

#endif /* __MINION_H__ */

