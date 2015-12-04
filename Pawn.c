#include "Pawn.h"

#include <stdlib.h>



Pawn_T * Pawn_Create(void)
{
   Pawn_T * pawn;
   pawn = malloc(sizeof(Pawn_T));
   Position_Set(&pawn->pos, 1, 2, 1);
   Mover_Init(&pawn->mover, &pawn->pos, 1.0f);
   return pawn;
}

void Pawn_Destroy(Pawn_T * pawn)
{
   free(pawn);
}

void Pawn_Update(Pawn_T * pawn, float seconds)
{
   Mover_Update(&pawn->mover, seconds);
}

