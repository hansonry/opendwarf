#include "PawnList.h"
#include <stdlib.h>
#include <string.h>

void PawnList_Init(PawnList_T * list)
{
   ObjectList_Init(&list->pawn_list, 0);
   PositionSet_Init(&list->visibility_set);
}

void PawnList_Destroy(PawnList_T * list)
{
   Pawn_T * pawn;
   size_t i, count;

   count = ObjectList_Count(&list->pawn_list);
   for(i = 0; i < count; i++)
   {
      pawn = ObjectList_Get(&list->pawn_list, i);
      Pawn_Destroy(pawn);
      free(pawn);
   }

   ObjectList_Destory(&list->pawn_list);
   PositionSet_Desstroy(&list->visibility_set);
}

void PawnList_Update(PawnList_T * list, float seconds)
{
   Pawn_T * pawn_ref;
   size_t i, count;

   count = ObjectList_Count(&list->pawn_list);

   for(i = count - 1; i < count; i--)
   {
      pawn_ref = ObjectList_Get(&list->pawn_list, i);
      if(KeepAlive_Update(&pawn_ref->k_alive) == e_KAS_Released)
      {
         ObjectList_RemoveFast(&list->pawn_list, i);
         Pawn_Destroy(pawn_ref);
         free(pawn_ref);
      }
      else
      {
         Pawn_Update(pawn_ref, seconds);
         Pawn_AddVisibility(pawn_ref, &list->visibility_set);
      }
   }


}

void PawnList_AddCopy(PawnList_T * list, const Pawn_T * pawn)
{
   Pawn_T * pawn_ref;

   pawn_ref = malloc(sizeof(Pawn_T));
   ObjectList_AddAtEnd(&list->pawn_list, pawn_ref);

   memcpy(pawn_ref, pawn, sizeof(Pawn_T));
}

Pawn_T * PawnList_Add(PawnList_T * list)
{

   Pawn_T * pawn_ref;

   pawn_ref = malloc(sizeof(Pawn_T));
   ObjectList_AddAtEnd(&list->pawn_list, pawn_ref);
   return pawn_ref;
}

Position_T * PawnList_GetVisibilityList(PawnList_T * list, size_t * count)
{
   return PositionSet_Get(&list->visibility_set, count);
}

