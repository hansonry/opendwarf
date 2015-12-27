#include "Pawn.h"

#include "AStar.h"
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

Pawn_T * Pawn_Create(MapChunk_T * map, MapItemList_T * map_item_list)
{
   Pawn_T * pawn;

   pawn = malloc(sizeof(Pawn_T));
   pawn->map = map;
   pawn->cmd_list = NULL;
   pawn->cmd_list_count = 0;
   pawn->cmd_index = 0;
   PawnCmdSystem_Init(&pawn->cmd_sys, map_item_list, 4, 2, 4, 1.0f);
   

   return pawn;
}

void Pawn_Destroy(Pawn_T * pawn)
{
   if(pawn->cmd_list != NULL)
   {
      free(pawn->cmd_list);
   }
   free(pawn);
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

void Pawn_SetJob(Pawn_T * pawn, Job_T * job)
{
   PawnCmd_T * cmd_list;
   size_t count;
   cmd_list = Job_CreateCmdList(job, &pawn->cmd_sys, pawn->map, &count);
   Pawn_SetComandList(pawn, cmd_list, count);
}

