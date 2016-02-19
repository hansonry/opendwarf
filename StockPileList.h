#ifndef __STOCKPILELIST_H__
#define __STOCKPILELIST_H__

#include "ObjectList.h"
#include "Position.h"
#include "RefCounter.h"

typedef struct StockPileList_S     StockPileList_T;
typedef struct StockPile_S         StockPile_T;
typedef struct StockPileRefCount_S StockPileRefCount_T;


struct StockPile_S
{
   Position_T pos;
};

struct StockPileRefCount_S
{
   RefCounter_T ref;
   StockPile_T  stockpile;
};

struct StockPileList_S
{
   ObjectList_T list;
};


void StockPileList_Init(StockPileList_T * list);
void StockPileList_Destroy(StockPileList_T * list);

void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos);
void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos);



#endif // __STOCKPILELIST_H__

