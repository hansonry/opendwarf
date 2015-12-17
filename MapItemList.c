#include "MapItemList.h"


void MapItemList_Init(MapItemList_T * list)
{
   ListMemory_Init(&list->mapitem_list, sizeof(MapItem_T), 0);
}

void MapItemList_Destory(MapItemList_T * list)
{
   ListMemory_Destory(&list->mapitem_list);
}

void MapItemList_Add(MapItemList_T * list, const MapItem_T * item)
{
   MapItem_T * mem;
   ListMemory_CopyAlloc(&list->mapitem_list, item, NULL);
}

void MapItemList_Remove(MapItemList_T * list, Item_T * item)
{
   size_t i, count;
   MapItem_T * item_list;

   item_list = ListMemory_Get(&list->mapitem_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(item_list[i].item == item)
      {
         ListMemory_FreeNow(&list->mapitem_list, i);
         break;
      }
   }
}


