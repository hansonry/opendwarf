#include "PawnList.h"


void PawnList_Init(PawnList_T * list)
{
   ObjectList_Init(&list->pawn_list);
   MemoryRefSet_Init(&list->pawn_mem, sizeof(Pawn_T), (MemoryRefSet_Freeer_T)Pawn_Destroy);
   PositionSet_Init(&list->visibility_set);
}

void PawnList_Destroy(PawnList_T * list)
{
   ObjectList_Destory(&list->pawn_list);
   MemoryRefSet_Destroy(&list->pawn_mem);
   PositionSet_Desstroy(&list->visibility_set);
}

void PawnList_Update(PawnList_T * list, float seconds)
{
   Pawn_T ** pawn_list;
   size_t i, count;

   MemoryRefSet_CheckCounts(&list->pawn_mem);
   PositionSet_Clear(&list->visibility_set);

   pawn_list = ObjectList_Get(&list->pawn_list, &count);

   for(i = 0; i < count; i++)
   {
      Pawn_Update(pawn_list[i], seconds);
      Pawn_AddVisibility(pawn_list[i], &list->visibility_set);
   }

}

void PawnList_AddCopy(PawnList_T * list, const Pawn_T * pawn)
{
   Pawn_T * l_pawn;

   l_pawn = MemoryRefSet_CopyAllocate(&list->pawn_mem, pawn);
   MemoryRefSet_Keep(&list->pawn_mem, l_pawn);
   ObjectList_Add(&list->pawn_list, l_pawn);
}

Pawn_T * PawnList_Add(PawnList_T * list)
{
   Pawn_T * pawn;
   pawn = MemoryRefSet_Allocate(&list->pawn_mem);
   MemoryRefSet_Keep(&list->pawn_mem, pawn);
   ObjectList_Add(&list->pawn_list, pawn);
   return pawn;
}

Position_T * PawnList_GetVisibilityList(PawnList_T * list, size_t * count)
{
   return PositionSet_Get(&list->visibility_set, count);
}

