#ifndef __PAWN_H__
#define __PAWN_H__
#include "Position.h"
#include "Mover.h"
#include "MoverControllerList.h"

typedef struct Pawn_S          Pawn_T;


struct Pawn_S
{
   Mover_T    mover;
   Position_T pos;
   MoverControllerList_T mover_ctrl;
};

Pawn_T * Pawn_Create(void);
void Pawn_Destroy(Pawn_T * pawn);


void Pawn_Update(Pawn_T * pawn, float seconds);
#endif // __PAWN_H__


