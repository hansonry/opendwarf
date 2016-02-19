#include "ItemList.h"
#include <stdlib.h>

void ItemList_Init(ItemList_T * list)
{
   ObjectList_Init(&list->item_list, 0);
   RefCounterQueue_Init(&list->mem_queue);
}

void ItemList_Destroy(ItemList_T * list)
{
   size_t i, count;
   Item_T * item;

   count = ObjectList_Count(&list->item_list);
   for(i = 0; i < count; i ++)
   {
      item = ObjectList_Get(&list->item_list, i);
      Item_Destory(item);
      free(item);
   }

   ObjectList_Destory(&list->item_list);
   RefCounterQueue_Destroy(&list->mem_queue);
}


void ItemList_Update(ItemList_T * list, float seconds)
{
   size_t count, i;
   Item_T * item;

   count = ObjectList_Count(&list->item_list);
   for(i = 0; i < count; i++)
   {
      item = ObjectList_Get(&list->item_list, i);
   }
   while((item = RefCounterQueue_Next(&list->mem_queue)) != NULL)
   {
      Item_Destory(item);
      free(item);
   }
}


Item_T * ItemList_Add(ItemList_T * list)
{
   Item_T * item;

   item = malloc(sizeof(Item_T));
   RefCounter_Keep(&item->ref);
   ObjectList_AddAtEnd(&list->item_list, item);
   RefCounterQueue_Add(&list->mem_queue, item, &item->ref);
   return item;
}


