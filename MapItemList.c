#include "MapItemList.h"
#include "MapItemEvent.h"
#include "LogicResources.h"
#include "MapItemEvent.h"


void MapItemEvent_AddMapItemRequest_Init(TypeMap_T * map, Item_T * item, const Position_T * pos)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "AddMapItemRequest");
   TypeMap_AddPointerKey(map, "Item", item);
   TypeMap_AddIntKey(map, "X", pos->x);
   TypeMap_AddIntKey(map, "Y", pos->y);
   TypeMap_AddIntKey(map, "Z", pos->z);
}

static void MapItemEvent_AddMapItemNotify_Init(TypeMap_T * map, int index)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "AddMapItemNotify");
   TypeMap_AddIntKey(map, "Index", index);
}

static void MapItemEvent_RemoveMapItemNotify_Init(TypeMap_T * map, int index)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "RemoveMapItemNotify");
   TypeMap_AddIntKey(map, "Index", index);
}

static void MapItemList_EventCallback(void * object, const TypeMap_T * event)
{
   MapItemList_T * list = object;
   MapItem_T map_item;

   if(TypeMap_IsStringEqual(event, "Type", "AddMapItemRequest") == 1)
   {
      map_item.item = TypeMap_GetPointer(event, "Item");
      map_item.x    = TypeMap_GetInt(event, "X");
      map_item.y    = TypeMap_GetInt(event, "Y");
      map_item.z    = TypeMap_GetInt(event, "Z");
      MapItemList_Add(list, &map_item);
   }

}

void MapItemList_Init(MapItemList_T * list)
{
   ManagerEvent_T * event_man;
   event_man = Resources_GetEventManager();

   ManagerEvent_RegisterCallback(event_man, list, MapItemList_EventCallback);
   ArrayList_Init(&list->mapitem_list, sizeof(MapItem_T), 0);
}

void MapItemList_Destory(MapItemList_T * list)
{
   ManagerEvent_T * event_man;

   event_man = Resources_GetEventManager();

   ManagerEvent_UnregisterCallback(event_man, list);
   ArrayList_Destory(&list->mapitem_list);
}

void MapItemList_Add(MapItemList_T * list, const MapItem_T * item)
{
   MapItem_T * mem;
   int index;
   ManagerEvent_T * event_man;
   TypeMap_T event;
   
   ArrayList_CopyAlloc(&list->mapitem_list, item, &index);

   event_man = Resources_GetEventManager();
   TypeMap_Init(&event);
   MapItemEvent_AddMapItemNotify_Init(&event, index);
   ManagerEvent_SendEvent(event_man, &event);
   TypeMap_Destory(&event);
}

void MapItemList_Remove(MapItemList_T * list, Item_T * item)
{
   size_t i, count;
   MapItem_T * item_list;
   int found, index;
   ManagerEvent_T * event_man;
   TypeMap_T event;

   found = 0;
   item_list = ArrayList_Get(&list->mapitem_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(item_list[i].item == item)
      {
         index = i;
         found = 1;
         break;
      }
   }
   if(found == 1)
   {
      event_man = Resources_GetEventManager();
      TypeMap_Init(&event);
      MapItemEvent_RemoveMapItemNotify_Init(&event, index);
      ManagerEvent_SendEvent(event_man, &event);
      TypeMap_Destory(&event);

      ArrayList_FreeNow(&list->mapitem_list, i);
   }
}


