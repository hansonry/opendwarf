#ifndef __STOCKPILELIST_H__
#define __STOCKPILELIST_H__

#include "ObjectList.h"
#include "StockPile.h"
#include "ListState.h"
#include "MapItemList.h"

typedef struct StockPileList_S     StockPileList_T;

struct StockPileList_S
{
   ObjectList_T list;
};


void StockPileList_Init(StockPileList_T * list);
void StockPileList_Destroy(StockPileList_T * list);

void StockPileList_Update(StockPileList_T * list, float seconds, 
                                                  MapItemList_T * map_item_list);

void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos);
void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos);



#endif // __STOCKPILELIST_H__

