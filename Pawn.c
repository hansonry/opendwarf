#include "Pawn.h"
#include "MapRay.h"

#include <stdlib.h>
#include <string.h>


static PawnCmd_T * Pawn_CreateMoveCmdList(const Position_T * pos_list, size_t count)
{
   PawnCmd_T * cmd_list;
   size_t i;
   cmd_list = malloc(sizeof(PawnCmd_T) * count);

   for(i = 0; i < count; i ++)
   {
      PawnCmd_Move_Init(&cmd_list[i], &pos_list[i]); 
   }

   return cmd_list;
}


void Pawn_Init(Pawn_T * pawn, MapChunk_T * map, MapItemList_T * map_item_list)
{

   pawn->map = map;
   pawn->cmd_list = NULL;
   pawn->cmd_list_count = 0;
   pawn->cmd_index = 0;
   PawnCmdSystem_Init(&pawn->cmd_sys, map_item_list, 4, 2, 4, 1.0f);
}

void Pawn_Destroy(Pawn_T * pawn)
{
   if(pawn->cmd_list != NULL)
   {
      free(pawn->cmd_list);
   }
}

void Pawn_SetComandList(Pawn_T * pawn, PawnCmd_T * cmd_list, size_t cmd_list_count)
{
   if(pawn->cmd_list != NULL)
   {
      free(pawn->cmd_list);
   }
   pawn->cmd_list = cmd_list;
   pawn->cmd_list_count = cmd_list_count;
   pawn->cmd_index = 0;

}

void Pawn_Update(Pawn_T * pawn, float seconds)
{
   // If there is no command running, and we have more commands to run
   // run the next command
   if(PawnCmdSystem_IsFinished(&pawn->cmd_sys) &&
      pawn->cmd_list != NULL && 
      pawn->cmd_index < pawn->cmd_list_count)
   {
      PawnCmdSystem_AttemptToSet(&pawn->cmd_sys, &pawn->cmd_list[pawn->cmd_index]);
      pawn->cmd_index ++;
   }

   PawnCmdSystem_Update(&pawn->cmd_sys, seconds);
}

#define VIS_RAD 3
void Pawn_AddVisibility(Pawn_T * pawn, PositionSet_T * set)
{
   Position_T pos;
   const Position_T * current_pos;
   int a, b;
   current_pos = &pawn->cmd_sys.position;



   for(a = -VIS_RAD; a < VIS_RAD + 1; a++)
   {
      for(b = -VIS_RAD; b < VIS_RAD + 1; b++)
      {
         pos.x = current_pos->x + a;
         pos.y = current_pos->y + b;
         pos.z = current_pos->z + VIS_RAD;
         MapRay_Cast(set, pawn->map, current_pos, &pos);

         pos.x = current_pos->x + a;
         pos.y = current_pos->y + b;
         pos.z = current_pos->z - VIS_RAD;
         MapRay_Cast(set, pawn->map, current_pos, &pos);

         pos.x = current_pos->x + a;
         pos.y = current_pos->y + VIS_RAD;
         pos.z = current_pos->z + b;
         MapRay_Cast(set, pawn->map, current_pos, &pos);

         pos.x = current_pos->x + a;
         pos.y = current_pos->y - VIS_RAD;
         pos.z = current_pos->z + b;
         MapRay_Cast(set, pawn->map, current_pos, &pos);

         pos.x = current_pos->x + VIS_RAD;
         pos.y = current_pos->y + a;
         pos.z = current_pos->z + b;
         MapRay_Cast(set, pawn->map, current_pos, &pos);
         
         pos.x = current_pos->x - VIS_RAD;
         pos.y = current_pos->y + a;
         pos.z = current_pos->z + b;
         MapRay_Cast(set, pawn->map, current_pos, &pos);
      }
   }
   
      

}

void Pawn_SetJob(Pawn_T * pawn, Job_T * job)
{
   PawnCmd_T * cmd_list;
   size_t count;
   cmd_list = Job_CreateCmdList(job, &pawn->cmd_sys, pawn->map, &count);
   Pawn_SetComandList(pawn, cmd_list, count);
}

