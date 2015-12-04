#ifndef __MOVERCONTROLERLIST_H__
#define __MOVERCONTROLERLIST_H__
#include "Position.h"
#include "Mover.h"
#include <stddef.h>

typedef struct MoverControllerList_S MoverControllerList_T;
struct MoverControllerList_S
{
   Mover_T * mover;
   const Position_T * pos_list;
   size_t pos_list_size;
   size_t index;
   int loop;
};

void MoverControllerList_Init(MoverControllerList_T * ctrl, Mover_T * mover, const Position_T * pos_list, size_t pos_list_size, int loop);

void MoverControllerList_Check(MoverControllerList_T * ctrl);



#endif // __MOVERCONTROLERLIST_H__


