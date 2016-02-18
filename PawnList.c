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
   ObjectList_Destory(&list->pawn_list);
   PositionSet_Desstroy(&list->visibility_set);
}

void PawnList_Update(PawnList_T * list, float seconds)
{
   PawnRefCount_T * pawn_ref;
   size_t i, count;

   count = ObjectList_Count(&list->pawn_list);

   for(i = count - 1; i < count; i--)
   {
      pawn_ref = ObjectList_Get(&list->pawn_list, i);
      if(RefCounter_ShouldDelete(&pawn_ref->ref))
      {
         ObjectList_RemoveFast(&list->pawn_list, i);
         Pawn_Destroy(&pawn_ref->pawn);
         free(pawn_ref);
      }
      else
      {
         Pawn_Update(&pawn_ref->pawn, seconds);
         Pawn_AddVisibility(&pawn_ref->pawn, &list->visibility_set);
      }
   }

}

void PawnList_AddCopy(PawnList_T * list, const Pawn_T * pawn)
{
   PawnRefCount_T * pawn_ref;

   pawn_ref = malloc(sizeof(PawnRefCount_T));
   RefCounter_Init(&pawn_ref->ref);
   RefCounter_Keep(&pawn_ref->ref);
   ObjectList_AddAtEnd(&list->pawn_list, pawn_ref);

   memcpy(&pawn_ref->pawn, pawn, sizeof(Pawn_T));
}

Pawn_T * PawnList_Add(PawnList_T * list)
{

   PawnRefCount_T * pawn_ref;

   pawn_ref = malloc(sizeof(PawnRefCount_T));
   RefCounter_Init(&pawn_ref->ref);
   RefCounter_Keep(&pawn_ref->ref);
   ObjectList_AddAtEnd(&list->pawn_list, pawn_ref);
   return &pawn_ref->pawn;
}

Position_T * PawnList_GetVisibilityList(PawnList_T * list, size_t * count)
{
   return PositionSet_Get(&list->visibility_set, count);
}

