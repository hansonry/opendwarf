#ifndef __PAWNLIST_H__
#define __PAWNLIST_H__
#include "Pawn.h"
#include "ObjectList.h"

typedef struct PawnList_S PawnList_T;
struct PawnList_S
{
   ObjectList_T pawn_list;
};

void PawnList_Init(PawnList_T * list);
void PawnList_Destroy(PawnList_T * list);

void PawnList_Update(PawnList_T * list, float seconds);

void PawnList_Add(PawnList_T * list, Pawn_T * pawn);


#endif // __PAWNLIST_H__

