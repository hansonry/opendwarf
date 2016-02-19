#include "StockPileList.h"
#include "StockPileEvent.h"
#include "LogicResources.h"
#include <string.h>
#include <stdlib.h>

void StockPileEvent_CreateStockpile_Init(TypeMap_T * event, const Position_T * pos)
{
   TypeMap_Clear(event);
   TypeMap_AddStringKey(event, "Type", "CreateStockpile");
   TypeMap_AddIntKey(event, "X", pos->x);
   TypeMap_AddIntKey(event, "Y", pos->y);
   TypeMap_AddIntKey(event, "Z", pos->z);


}

static void StockPileList_ReciveEvent(void * object, const TypeMap_T * event)
{
   StockPileList_T * list = object;
   Position_T pos;

   if(TypeMap_IsStringEqual(event, "Type", "CreateStockpile") == 1)
   {
      pos.x = TypeMap_GetInt(event, "X");
      pos.y = TypeMap_GetInt(event, "Y");
      pos.z = TypeMap_GetInt(event, "Z");
      StockPileList_AddPosition(list, &pos);
   }
}

void StockPileList_Init(StockPileList_T * list)
{
   ManagerEvent_T * event_man;
   ObjectList_Init(&list->list, 0);
   event_man = Resources_GetEventManager();
   ManagerEvent_RegisterCallback(event_man, list, StockPileList_ReciveEvent);
}

void StockPileList_Destroy(StockPileList_T * list)
{
   ManagerEvent_T * event_man;
   size_t i, count;
   StockPileRefCount_T * stock_rc;
   count = ObjectList_Count(&list->list);
   for(i = 0; i < count; i++)
   {
      stock_rc = ObjectList_Get(&list->list, i);
      free(stock_rc);
   }

   ObjectList_Destory(&list->list);

   event_man = Resources_GetEventManager();
   ManagerEvent_UnregisterCallback(event_man, list); 
}


void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos)
{
   StockPileRefCount_T * stock_rc;

   stock_rc = malloc(sizeof(StockPileRefCount_T));
   Position_Copy(&stock_rc->stockpile.pos, pos);
   RefCounter_Init(&stock_rc->ref);
   ObjectList_AddAtEnd(&list->list, stock_rc);
}

void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos)
{
   StockPileRefCount_T * stock_rc;
   size_t i, count;

   count = ObjectList_Count(&list->list);
   for(i = 0; i < count; i++)
   {
      stock_rc = ObjectList_Get(&list->list, i);
      if(Position_IsEqual(&stock_rc->stockpile.pos, pos))
      {
         ObjectList_RemoveFast(&list->list, i);
         break;
      }
   }
}



