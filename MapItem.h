#ifndef __MAPITEM_H__
#define __MAPITEM_H__
#include "Item.h"
#include "Position.h"
#include "KeepAlive.h"

typedef struct StockPile_S StockPile_T;
typedef struct MapItem_S   MapItem_T;

struct MapItem_S
{
   KeepAlive_T   k_alive;
   Item_T      * item;
   Position_T    pos;
   StockPile_T * claimed_stockpile;
};


void MapItem_Init(MapItem_T * map_item, int x, int y, int z, Item_T * item);
void MapItem_Destroy(MapItem_T * map_item);




#endif // __MAPITEM_H__


