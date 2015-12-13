#include "Pawn.h"

#include "AStar.h"
#include <stdlib.h>
#include <string.h>

static const Position_T plist[4] =
{
   { 0, 2, 0 },
   { 1, 2, 0 },
   { 2, 2, 0 },
   { 2, 2, 1 },
};

Pawn_T * Pawn_Create(MapChunk_T * map)
{
   Pawn_T * pawn;
   AStar_T astar;
   Position_T end;
   size_t count;
   pawn = malloc(sizeof(Pawn_T));
   pawn->map = map;
   pawn->cmd_list = NULL;
   pawn->cmd_list_count = 0;
   pawn->cmd_index = 0;
   pawn->cmd_state = e_PCS_NoCommand;
   Position_Set(&pawn->pos, 4, 2, 4);
   Mover_Init(&pawn->mover, &pawn->pos, 1.0f);
   MoverControllerList_Init(&pawn->mover_ctrl, &pawn->mover, 1);
   Position_Set(&end, 0, 2, 0);
   AStar_Init(&astar, pawn->map, &pawn->pos, &end);
   if(AStar_Run(&astar))
   {
      pawn->path_list = AStar_CreatePositionList(&astar, &count);
      MoverControllerList_SetPath(&pawn->mover_ctrl, pawn->path_list, count);
   }
   else
   {
      MoverControllerList_SetPath(&pawn->mover_ctrl, plist, 4);

   }

   AStar_Destroy(&astar);
   return pawn;
}

void Pawn_Destroy(Pawn_T * pawn)
{
   if(pawn->path_list != NULL)
   {
      free(pawn->path_list);
   }
   free(pawn);
}

void Pawn_SetComandList(Pawn_T * pawn, PawnCmd_T * cmd_list, size_t cmd_list_count)
{
   pawn->cmd_list = cmd_list;
   pawn->cmd_list_count = cmd_list_count;
   pawn->cmd_index = 0;
  
   if(pawn->cmd_state == e_PCS_NoCommand)
   {
      pawn->cmd_state == e_PCS_FinishedCommand;
   }

}

static void Pawn_InitCurrentCommand(Pawn_T * pawn)
{
   pawn->cmd_state = e_PCS_RunningCommand;

}

static Pawn_UpdateCurrentCommand(Pawn_T * pawn)
{
}


static void Pawn_UpdateCommand(Pawn_T * pawn, float seconds)
{
   if(pawn->cmd_state == e_PCS_NoCommand && 
      pawn->cmd_list != NULL && 
      pawn->cmd_index < pawn->cmd_list_count)
   {
      memcpy(&pawn->current_command, &pawn->cmd_list[pawn->cmd_index], sizeof(PawnCmd_T));
      Pawn_InitCurrentCommand(pawn);
   }

   if(pawn->cmd_index == e_PCS_RunningCommand)
   {
      Pawn_UpdateCurrentCommand(pawn);
   }

}

void Pawn_Update(Pawn_T * pawn, float seconds)
{
   Pawn_UpdateCommand(pawn, seconds);
   Mover_Update(&pawn->mover, seconds);
   MoverControllerList_Check(&pawn->mover_ctrl);
}

