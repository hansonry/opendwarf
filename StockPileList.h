#ifndef __STOCKPILELIST_H__
#define __STOCKPILELIST_H__

#include "ListMemory.h"
#include "Position.h"

typedef struct StockPileList_S StockPileList_T;

struct StockPileList_S
{
   ListMemory_T list;
};


void StockPileList_Init(StockPileList_T * list);
void StockPileList_Destroy(StockPileList_T * list);

void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos);
void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos);



#endif // __STOCKPILELIST_H__

