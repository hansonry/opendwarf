#include "MoverControllerList.h"

void MoverControllerList_Init(MoverControllerList_T * ctrl, Mover_T * mover, int loop)
{
   ctrl->mover = mover;
   ctrl->pos_list = NULL;
   ctrl->pos_list_size = 0;
   ctrl->loop = loop;
   ctrl->index = 0;
}

void MoverControllerList_SetPath(MoverControllerList_T * ctrl, const Position_T * pos_list, size_t pos_list_size)
{
   ctrl->pos_list = pos_list;
   ctrl->pos_list_size = pos_list_size;
   ctrl->index = 0;
}


void MoverControllerList_Check(MoverControllerList_T * ctrl)
{
   int active;
   if(ctrl->pos_list == NULL)
   {
      active = 0;
   }
   else if(ctrl->index < ctrl->pos_list_size)
   {
      active = 1;
   }
   else if(ctrl->loop == 1)
   {
      active = 1;
      ctrl->index = 0;
   }
   else
   {
      active = 0;
   }


   if(active == 1 && !Mover_IsMoving(ctrl->mover))
   {
      Mover_MoveTo(ctrl->mover, &ctrl->pos_list[ctrl->index]);
      ctrl->index ++;
   }
}

