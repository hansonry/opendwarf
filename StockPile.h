#ifndef __STOCKPILE_H__
#define __STOCKPILE_H__
#include "Position.h"
#include "KeepAlive.h"
#include "Job.h"

typedef struct StockPile_S StockPile_T;
typedef struct MapItem_S   MapItem_T;

struct StockPile_S
{
   KeepAlive_T    k_alive;
   Position_T     pos;
   MapItem_T    * claimed_map_item;
   Job_T          job;
};

void StockPile_Init(StockPile_T * stockpile, int x, int y, int z);
void StockPile_Destroy(StockPile_T * stockpile);


#endif // __STOCKPILE_H__

