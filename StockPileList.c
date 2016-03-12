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
   StockPile_T * stock_rc;
   count = ObjectList_Count(&list->list);
   for(i = 0; i < count; i++)
   {
      stock_rc = ObjectList_Get(&list->list, i);
      StockPile_Destroy(stock_rc);
      free(stock_rc);
   }

   ObjectList_Destory(&list->list);

   event_man = Resources_GetEventManager();
   ManagerEvent_UnregisterCallback(event_man, list); 
}

void StockPileList_Update(StockPileList_T * list, float seconds, 
                                                  MapItemList_T * map_item_list)
{
   size_t i, count, k, item_count;
   StockPile_T * stockpile_rc;
   MapItem_T * item_rc;

   
   item_count = ObjectList_Count(&map_item_list->mapitem_list);
   k = 0;
   count = ObjectList_Count(&list->list);
   for(i = count - 1; i < count; i --)
   {
      stockpile_rc = ObjectList_Get(&list->list, i);

      if(KeepAlive_Update(&stockpile_rc->k_alive) == e_KAS_Released)
      {
         ObjectList_RemoveFast(&list->list, i);
         StockPile_Destroy(stockpile_rc);
         free(stockpile_rc);
      }
      else
      {

         // Find Map Item
         while((k < item_count) && 
               (stockpile_rc->claimed_map_item == NULL))
         {
            item_rc = ObjectList_Get(&map_item_list->mapitem_list, k);
            if(item_rc->claimed_stockpile == NULL)
            {
               stockpile_rc->claimed_map_item = item_rc;
               item_rc->claimed_stockpile     = stockpile_rc;
            }
            k++;
         }

         if(stockpile_rc->claimed_map_item != NULL)
         {
            KeepAlive_KeepAlive(&stockpile_rc->claimed_map_item->k_alive);
         }

      }
   }
   

}

void StockPileList_AddPosition(StockPileList_T * list, const Position_T * pos)
{
   StockPile_T * stock_rc;

   stock_rc = malloc(sizeof(StockPile_T));
   StockPile_Init(stock_rc, pos->x, pos->y, pos->z);
   ObjectList_AddAtEnd(&list->list, stock_rc);
}

void StockPileList_RemovePosition(StockPileList_T * list, const Position_T * pos)
{
   StockPile_T * stock_rc;
   size_t i, count;

   count = ObjectList_Count(&list->list);
   for(i = 0; i < count; i++)
   {
      stock_rc = ObjectList_Get(&list->list, i);
      if(Position_IsEqual(&stock_rc->pos, pos))
      {
         ObjectList_RemoveFast(&list->list, i);
         KeepAlive_RequestRelease(&stock_rc->k_alive);
         break;
      }
   }
}




