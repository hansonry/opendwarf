#include "PawnList.h"


void PawnList_Init(PawnList_T * list)
{
   ObjectList_Init(&list->pawn_list);
}

void PawnList_Destroy(PawnList_T * list)
{
   ObjectList_Destory(&list->pawn_list);
}

void PawnList_Add(PawnList_T * list, Pawn_T * pawn)
{
   ObjectList_Add(&list->pawn_list, pawn);
}


