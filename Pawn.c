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

static PawnCmd_T * Pawn_CreateMoveCmdList(const Position_T * pos_list, size_t count)
{
   PawnCmd_T * cmd_list;
   size_t i;
   cmd_list = malloc(sizeof(PawnCmd_T) * count);

   for(i = 0; i < count; i ++)
   {
      PawnCmd_InitMove(&cmd_list[i], &pos_list[i]); 
   }

   return cmd_list;
}

Pawn_T * Pawn_Create(MapChunk_T * map)
{
   Pawn_T * pawn;
   AStar_T astar;
   Position_T end;   
   size_t count;
   Position_T * path_list;
   PawnCmd_T * cmd_list;

   pawn = malloc(sizeof(Pawn_T));
   pawn->map = map;
   pawn->cmd_list = NULL;
   pawn->cmd_list_count = 0;
   pawn->cmd_index = 0;
   PawnCmdSystem_Init(&pawn->cmd_sys, 4, 2, 4, 1.0f);
   Position_Set(&end, 0, 2, 0);
   AStar_Init(&astar, pawn->map, &pawn->cmd_sys.position, &end);
   if(AStar_Run(&astar))
   {
      path_list = AStar_CreatePositionList(&astar, &count);
      cmd_list = Pawn_CreateMoveCmdList(path_list, count);
      free(path_list);
   }
   else
   {
      count = 4;
      cmd_list = Pawn_CreateMoveCmdList(plist, count);
   }
   
   Pawn_SetComandList(pawn, cmd_list, count);

   AStar_Destroy(&astar);
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

