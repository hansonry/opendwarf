#include "PawnList.h"


void PawnList_Init(PawnList_T * list)
{
   ObjectList_Init(&list->pawn_list);
   MemoryRefSet_Init(&list->pawn_mem, sizeof(Pawn_T), (MemoryRefSet_Freeer_T)Pawn_Destroy);
}

void PawnList_Destroy(PawnList_T * list)
{
   ObjectList_Destory(&list->pawn_list);
   MemoryRefSet_Destroy(&list->pawn_mem);
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

void PawnList_Add(PawnList_T * list, const Pawn_T * pawn)
{
   Pawn_T * l_pawn;

   l_pawn = MemoryRefSet_CopyAllocate(&list->pawn_mem, pawn);
   MemoryRefSet_Keep(&list->pawn_mem, l_pawn);
   ObjectList_Add(&list->pawn_list, l_pawn);
}


