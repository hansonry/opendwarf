#include "ItemList.h"
#include <stdlib.h>

void ItemList_Init(ItemList_T * list)
{
   ObjectList_Init(&list->item_list, 0);
}

void ItemList_Destroy(ItemList_T * list)
{
   ObjectList_Destory(&list->item_list);
}


void ItemList_CleanMemory(ItemList_T * list)
{
   size_t count, i;
   ItemRefCount_T * item;

   count = ObjectList_Count(&list->item_list);
   for(i = count - 1; i < count; i--)
   {
      item = ObjectList_Get(&list->item_list, i);
      if(RefCounter_ShouldDelete(&item->ref))
      {
         Item_Destory(&item->item);
         free(item);
         ObjectList_RemoveFast(&list->item_list, i);
      }
   }
}


Item_T * ItemList_Add(ItemList_T * list)
{
   ItemRefCount_T * item;

   item = malloc(sizeof(ItemRefCount_T));
   RefCounter_Init(&item->ref);
   RefCounter_Keep(&item->ref);
   ObjectList_AddAtEnd(&list->item_list, item);
   return &item->item;
}


