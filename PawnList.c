#include "PawnList.h"


void PawnList_Init(PawnList_T * list)
{
   ObjectList_Init(&list->pawn_list);
}

void PawnList_Destroy(PawnList_T * list)
{
   ObjectList_Destory(&list->pawn_list);
}

void PawnList_Update(PawnList_T * list, float seconds)
{
   Pawn_T ** pawn_list;
   size_t i, count;

   pawn_list = ObjectList_Get(&list->pawn_list, &count);

   for(i = 0; i < count; i++)
   {
      Pawn_Update(pawn_list[i], seconds);
   }
}

void PawnList_Add(PawnList_T * list, Pawn_T * pawn)
{
   ObjectList_Add(&list->pawn_list, pawn);
}


