#include "MapItem.h"
#include "StockPile.h"
#include <stddef.h>

void MapItem_Init(MapItem_T * map_item, int x, int y, int z, Item_T * item)
{
   RefCounter_Init(&map_item->ref);
   Position_Set(&map_item->pos, x, y, z);
   map_item->item = item;
   map_item->claimed_stockpile = NULL;
}

void MapItem_Unlink(MapItem_T * map_item)
{
   if(map_item->claimed_stockpile != NULL)
   {
      RefCounter_Release(&map_item->claimed_stockpile->ref);
      if(map_item->claimed_stockpile->claimed_map_item == map_item)
      {
         RefCounter_Release(&map_item->ref);
         map_item->claimed_stockpile->claimed_map_item = NULL;
      }
   }
}

void MapItem_Destroy(MapItem_T * map_item)
{
}

