#include "StockPileList.h"


void StockPileList_Init(StockPileList_T * list)
{
   ListMemory_Init(&list->list, sizeof(Position_T), 0);
}

void StockPileList_Destroy(StockPileList_T * list)
{
   ListMemory_Destory(&list->list);
}


void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos)
{
   ListMemory_CopyAlloc(&list->list, pos, NULL);
}

void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos)
{
   Position_T * pos_list;
   size_t i, count;

   pos_list = ListMemory_Get(&list->list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(Position_IsEqual(&pos_list[i], pos))
      {
         ListMemory_FreeNow(&list->list, i);
         break;
      }
   }
}



