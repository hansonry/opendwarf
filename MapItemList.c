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
   ListMemory_CopyAlloc(&list->mapitem_list, item);
}


