#ifndef __PAWN_H__
#define __PAWN_H__
#include "Position.h"
#include "Mover.h"
#include "MoverControllerList.h"
#include "MapChunk.h"

typedef struct Pawn_S          Pawn_T;


struct Pawn_S
{
   Mover_T    mover;
   Position_T pos;
   Position_T * path_list;
   MoverControllerList_T mover_ctrl;
   MapChunk_T * map;
};

Pawn_T * Pawn_Create(MapChunk_T * map);
void Pawn_Destroy(Pawn_T * pawn);


void Pawn_Update(Pawn_T * pawn, float seconds);
#endif // __PAWN_H__


