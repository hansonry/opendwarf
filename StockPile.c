#include "StockPile.h"
#include "MapItem.h"
#include <stddef.h>

void StockPile_Init(StockPile_T * stockpile, int x, int y, int z)
{
   Position_Set(&stockpile->pos, x, y, z);
   RefCounter_Init(&stockpile->ref);
   stockpile->claimed_map_item = NULL;
}



void StockPile_Unlink(StockPile_T * stockpile)
{
   if(stockpile->claimed_map_item != NULL)
   {
      RefCounter_Release(&stockpile->claimed_map_item->ref);
      if(stockpile->claimed_map_item->claimed_stockpile == stockpile)
      {
         RefCounter_Release(&stockpile->ref);
         stockpile->claimed_map_item->claimed_stockpile = NULL;
      }
   }
}

void StockPile_Destroy(StockPile_T * stockpile)
{
}



