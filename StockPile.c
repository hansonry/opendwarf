#include "StockPile.h"
#include "MapItem.h"
#include <stddef.h>

void StockPile_Init(StockPile_T * stockpile, int x, int y, int z)
{
   Position_Set(&stockpile->pos, x, y, z);
   KeepAlive_Init(&stockpile->k_alive);
   stockpile->claimed_map_item = NULL;
}


void StockPile_Destroy(StockPile_T * stockpile)
{
}



