#include "Pawn.h"

#include <stdlib.h>

Pawn_T * Pawn_Create(void)
{
   Pawn_T * pawn;
   pawn = malloc(sizeof(Pawn_T));
   pawn->x = 1;
   pawn->y = 2;
   pawn->z = 1;
   return pawn;
}

void Pawn_Destroy(Pawn_T * pawn)
{
   free(pawn);
}

