#ifndef __MAPITEMLIST_H__
#define __MAPITEMLIST_H__

#include "Item.h"
#include "ListMemory.h"

typedef struct MapItem_S         MapItem_T;
typedef struct MapItemList_S     MapItemList_T;


struct MapItem_S
{
   Item_T * item;
   int x;
   int y;
   int z;
};

struct MapItemList_S
{
   ListMemory_T mapitem_list;
};

void MapItemList_Init(MapItemList_T * list);
void MapItemList_Destory(MapItemList_T * list);

void MapItemList_Add(MapItemList_T * list, const MapItem_T * item);

void MapItemList_Remove(MapItemList_T * list, Item_T * item);



#endif // __MAPITEMLIST_H__

