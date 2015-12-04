#include "Pawn.h"

#include <stdlib.h>

static const Position_T plist[4] =
{
   { 0, 2, 0 },
   { 1, 2, 0 },
   { 2, 2, 0 },
   { 2, 2, 1 },
};

Pawn_T * Pawn_Create(void)
{
   Pawn_T * pawn;
   pawn = malloc(sizeof(Pawn_T));
   Position_Set(&pawn->pos, 1, 2, 1);
   Mover_Init(&pawn->mover, &pawn->pos, 1.0f);
   MoverControllerList_Init(&pawn->mover_ctrl, &pawn->mover, 1);
   MoverControllerList_SetPath(&pawn->mover_ctrl, plist, 4);
   return pawn;
}

void Pawn_Destroy(Pawn_T * pawn)
{
   free(pawn);
}

void Pawn_Update(Pawn_T * pawn, float seconds)
{
   Mover_Update(&pawn->mover, seconds);
   MoverControllerList_Check(&pawn->mover_ctrl);
}

