#include "Job.h"
#include "AStar.h"


void Job_None_Init(Job_T * job)
{
   job->type = e_JT_None;
}

void Job_PickupItem_Init(Job_T * job, Item_T * item, const Position_T * item_pos)
{
   job->type = e_JT_PickupItem;
   job->data.pickup_item.item = item;
   Position_Copy(&job->data.pickup_item.item_pos, item_pos);
}

void Job_MoveItem_Init(Job_T * job, Item_T * item, const Position_T * item_pos, const Position_T * drop_pos)
{
   job->type = e_JT_MoveItem;
   job->data.move_item.item = item;
   Position_Copy(&job->data.move_item.item_pos, item_pos);
   Position_Copy(&job->data.move_item.drop_pos, drop_pos);
}


static PawnCmd_T * Job_PickupItem_CreateCmdList(Job_PickupItem_T * job, PawnCmdSystem_T * sys)
{
   return NULL;
}

static PawnCmd_T * Job_MoveItem_CreateCmdList(Job_MoveItem_T * job, PawnCmdSystem_T * sys)
{
   return NULL;
}

PawnCmd_T * Job_CreateCmdList(Job_T * job, PawnCmdSystem_T * sys)
{
   PawnCmd_T * list;
   switch(job->type)
   {
   case e_JT_PickupItem:
      list = Job_PickupItem_CreateCmdList(&job->data.pickup_item, sys);
      break;
   case e_JT_MoveItem:
      list = Job_MoveItem_CreateCmdList(&job->data.move_item, sys);
      break;
   case e_JT_None:
   default:
      list = NULL;
      break;
   }
   return list;
}


