#include "ItemList.h"
#include <stdlib.h>

void ItemList_Init(ItemList_T * list)
{
   ObjectList_Init(&list->item_list, 0);
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
}


void ItemList_Update(ItemList_T * list, float seconds)
{
   size_t count, i;
   Item_T * item;

   count = ObjectList_Count(&list->item_list);
   for(i = count - 1 ; i < count; i--)
   {
      item = ObjectList_Get(&list->item_list, i);
      if(KeepAlive_Update(&item->k_alive) == e_KAS_Released)
      {
         ObjectList_RemoveFast(&list->item_list, i);
         Item_Destory(item);
         free(item);
      }
   }

}


Item_T * ItemList_Add(ItemList_T * list, ItemType_T type)
{
   Item_T * item;

   item = malloc(sizeof(Item_T));
   Item_Init(item, type);
   ObjectList_AddAtEnd(&list->item_list, item);
   return item;
}


