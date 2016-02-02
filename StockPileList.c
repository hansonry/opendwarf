#include "StockPileList.h"
#include "StockPileEvent.h"
#include "LogicResources.h"


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
   ArrayList_Init(&list->list, sizeof(Position_T), 0);
   event_man = Resources_GetEventManager();
   ManagerEvent_RegisterCallback(event_man, list, StockPileList_ReciveEvent);
}

void StockPileList_Destroy(StockPileList_T * list)
{
   ManagerEvent_T * event_man;
   ArrayList_Destory(&list->list);

   event_man = Resources_GetEventManager();
   ManagerEvent_UnregisterCallback(event_man, list); 
}


void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos)
{
   ArrayList_CopyAlloc(&list->list, pos, NULL);
}

void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos)
{
   Position_T * pos_list;
   size_t i, count;

   pos_list = ArrayList_Get(&list->list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(Position_IsEqual(&pos_list[i], pos))
      {
         ArrayList_FreeNow(&list->list, i);
         break;
      }
   }
}



