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
   pawn->cmd_state = e_PCS_FinishedCommand;
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
static void Pawn_SetCurrentCommand(Pawn_T * pawn, const PawnCmd_T * cmd)
{
   memcpy(&pawn->current_command, cmd, sizeof(PawnCmd_T));
   pawn->cmd_state = e_PCS_CommandLoaded;
}

void Pawn_SetComandList(Pawn_T * pawn, PawnCmd_T * cmd_list, size_t cmd_list_count)
{
   pawn->cmd_list = cmd_list;
   pawn->cmd_list_count = cmd_list_count;
   pawn->cmd_index = 0;

}

static void Pawn_InitCurrentCommand(Pawn_T * pawn)
{
   pawn->cmd_state = e_PCS_RunningCommand;

}

static Pawn_UpdateCurrentCommand(Pawn_T * pawn, float seconds)
{
   if(pawn->cmd_state == e_PCS_CommandLoaded)
   {
      switch(pawn->current_command.type)
      {
      case e_PCT_MoveTo:
         break;
      case e_PCT_PickUp:
         break;
      case e_PCT_Drop:
         break;
      case e_PCT_Wait:
      default:
         break;
      }
      // INITS
      pawn->cmd_state = e_PCS_RunningCommand;
   }

   if(pawn->cmd_state == e_PCS_RunningCommand)
   {
      switch(pawn->current_command.type)
      {
      case e_PCT_MoveTo:
         break;
      case e_PCT_PickUp:
         break;
      case e_PCT_Drop:
         break;
      case e_PCT_Wait:
      default:
         break;
      }
      // RUNNINGS
   }

}


static void Pawn_UpdateCommand(Pawn_T * pawn, float seconds)
{

   if(pawn->cmd_state == e_PCS_FinishedCommand)
   {
      if(pawn->cmd_list != NULL && 
         pawn->cmd_index < pawn->cmd_list_count)
      {
         Pawn_SetCurrentCommand(pawn, &pawn->cmd_list[pawn->cmd_index]);
         pawn->cmd_index ++;
      }
   }
   else
   {
      Pawn_UpdateCurrentCommand(pawn, seconds);
   }
}

void Pawn_Update(Pawn_T * pawn, float seconds)
{
   Pawn_UpdateCommand(pawn, seconds);
   Mover_Update(&pawn->mover, seconds);
   MoverControllerList_Check(&pawn->mover_ctrl);
}

