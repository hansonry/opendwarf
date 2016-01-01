#ifndef __PAWNLIST_H__
#define __PAWNLIST_H__
#include <stddef.h>
#include "Pawn.h"
#include "Position.h"
#include "ListMemory.h"
#include "ObjectList.h"
#include "MemoryRefSet.h"

typedef struct PawnList_S PawnList_T;
struct PawnList_S
{
   ObjectList_T   pawn_list;
   MemoryRefSet_T pawn_mem;
   ListMemory_T   visibility_list;
};

void PawnList_Init(PawnList_T * list);
void PawnList_Destroy(PawnList_T * list);

void PawnList_Update(PawnList_T * list, float seconds);

void PawnList_AddCopy(PawnList_T * list, const Pawn_T * pawn);
Pawn_T * PawnList_Add(PawnList_T * list);

Position_T * PawnList_GetVisibilityList(PawnList_T * list, size_t * count);


#endif // __PAWNLIST_H__

