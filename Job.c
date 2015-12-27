#include "Job.h"
#include "AStar.h"
#include "ListMemory.h"

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


static void Job_AppendPath(ListMemory_T * cmd_list, MapChunk_T * map, const Position_T * start, const Position_T * end)
{
   AStar_T      astar;
   Position_T   * pos_list;
   size_t       count, i;
   PawnCmd_T    cmd;

   AStar_Init(&astar, map, start, end);
   AStar_Run(&astar);

   pos_list = AStar_CreatePositionList(&astar, &count);

   for(i = 0; i < count; i++)
   {
      PawnCmd_Move_Init(&cmd, &pos_list[i]);
      ListMemory_CopyAlloc(cmd_list, &cmd, NULL);
   }

   AStar_Destroy(&astar);
}

static PawnCmd_T * Job_PickupItem_CreateCmdList(Job_PickupItem_T * job, PawnCmdSystem_T * sys, MapChunk_T * map, size_t * count)
{
   ListMemory_T list;
   PawnCmd_T    cmd;
   PawnCmd_T    * cmd_list;

   ListMemory_Init(&list, sizeof(PawnCmd_T), 0);

   Job_AppendPath(&list, map, &sys->position, &job->item_pos);

   PawnCmd_Pickup_Init(&cmd, job->item);
   ListMemory_CopyAlloc(&list, &cmd, NULL);



   cmd_list = ListMemory_GetCopy(&list, count, NULL);

   ListMemory_Destory(&list);

   return cmd_list;
}

static PawnCmd_T * Job_MoveItem_CreateCmdList(Job_MoveItem_T * job, PawnCmdSystem_T * sys, MapChunk_T * map, size_t * count)
{
   ListMemory_T list;
   PawnCmd_T    cmd;
   PawnCmd_T    * cmd_list;


   ListMemory_Init(&list, sizeof(PawnCmd_T), 0);

   Job_AppendPath(&list, map, &sys->position, &job->item_pos);

   PawnCmd_Pickup_Init(&cmd, job->item);
   ListMemory_CopyAlloc(&list, &cmd, NULL);

   Job_AppendPath(&list, map, &job->item_pos, &job->drop_pos);

   PawnCmd_Drop_Init(&cmd);
   ListMemory_CopyAlloc(&list, &cmd, NULL);

   cmd_list = ListMemory_GetCopy(&list, count, NULL);

   ListMemory_Destory(&list);

   return cmd_list;
}

PawnCmd_T * Job_CreateCmdList(Job_T * job, PawnCmdSystem_T * sys, MapChunk_T * map, size_t * count)
{
   PawnCmd_T * list;
   switch(job->type)
   {
   case e_JT_PickupItem:
      list = Job_PickupItem_CreateCmdList(&job->data.pickup_item, sys, map, count);
      break;
   case e_JT_MoveItem:
      list = Job_MoveItem_CreateCmdList(&job->data.move_item, sys, map, count);
      break;
   case e_JT_None:
   default:
      list = NULL;
      break;
   }
   return list;
}


