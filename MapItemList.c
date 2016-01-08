#include "MapItemList.h"
#include "MapItemEvent.h"
#include "LogicResources.h"
#include "MapItemEvent.h"


void MapItemEvent_CreateMapItem_Init(TypeMap_T * map, Item_T * item, const Position_T * pos)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "CreateMapItem");
   TypeMap_AddPointerKey(map, "Item", item);
   TypeMap_AddIntKey(map, "X", pos->x);
   TypeMap_AddIntKey(map, "Y", pos->y);
   TypeMap_AddIntKey(map, "Z", pos->z);
}

static void MapItemList_EventCallback(void * object, const TypeMap_T * event)
{
   MapItemList_T * list = object;
   MapItem_T map_item;

   if(TypeMap_IsStringEqual(event, "Type", "CreateMapItem") == 1)
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
   ListMemory_Init(&list->mapitem_list, sizeof(MapItem_T), 0);
}

void MapItemList_Destory(MapItemList_T * list)
{
   ManagerEvent_T * event_man;

   event_man = Resources_GetEventManager();

   ManagerEvent_UnregisterCallback(event_man, list);
   ListMemory_Destory(&list->mapitem_list);
}

void MapItemList_Add(MapItemList_T * list, const MapItem_T * item)
{
   MapItem_T * mem;
   ListMemory_CopyAlloc(&list->mapitem_list, item, NULL);
}

void MapItemList_Remove(MapItemList_T * list, Item_T * item)
{
   size_t i, count;
   MapItem_T * item_list;

   item_list = ListMemory_Get(&list->mapitem_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(item_list[i].item == item)
      {
         ListMemory_FreeNow(&list->mapitem_list, i);
         break;
      }
   }
}


