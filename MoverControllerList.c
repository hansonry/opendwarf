#include "MoverControllerList.h"

void MoverControllerList_Init(MoverControllerList_T * ctrl, Mover_T * mover, const Position_T * pos_list, size_t pos_list_size, int loop)
{
   ctrl->mover = mover;
   ctrl->pos_list = pos_list;
   ctrl->pos_list_size = pos_list_size;
   ctrl->loop = loop;
   ctrl->index = 0;
}

void MoverControllerList_Check(MoverControllerList_T * ctrl)
{
   if(!Mover_IsMoving(ctrl->mover))
   {
      if(ctrl->index < ctrl->pos_list_size)
      {
         Mover_MoveTo(ctrl->mover, &ctrl->pos_list[ctrl->index]);
         ctrl->index ++;
      }

   }
}

