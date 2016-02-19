#ifndef __MAPITEMLIST_H__
#define __MAPITEMLIST_H__

#include "ObjectList.h"
#include "RefCounter.h"
#include "ListState.h"
#include "MapItem.h"
#include "RefCounterQueue.h"

typedef struct MapItemList_S     MapItemList_T;




struct MapItemList_S
{
   ObjectList_T      mapitem_list;
   RefCounterQueue_T mem_queue;
};

void MapItemList_Init(MapItemList_T * list);
void MapItemList_Destory(MapItemList_T * list);

void MapItemList_Update(MapItemList_T * list, float seconds);

void MapItemList_Add(MapItemList_T * list, const MapItem_T * item);

void MapItemList_Remove(MapItemList_T * list, Item_T * item);



#endif // __MAPITEMLIST_H__

