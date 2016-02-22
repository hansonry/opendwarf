#include "MapItemList.h"
#include "MapItemEvent.h"
#include "LogicResources.h"
#include "MapItemEvent.h"
#include <string.h>
#include <stdlib.h>


void MapItemEvent_AddMapItemRequest_Init(TypeMap_T * map, Item_T * item, const Position_T * pos)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "AddMapItemRequest");
   TypeMap_AddPointerKey(map, "Item", item);
   TypeMap_AddIntKey(map, "X", pos->x);
   TypeMap_AddIntKey(map, "Y", pos->y);
   TypeMap_AddIntKey(map, "Z", pos->z);
}

static void MapItemEvent_AddMapItemNotify_Init(TypeMap_T * map, MapItem_T * map_item)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "AddMapItemNotify");
   TypeMap_AddPointerKey(map, "MapItemAddress", map_item);
}

static void MapItemEvent_RemoveMapItemNotify_Init(TypeMap_T * map, MapItem_T * map_item)
{
   TypeMap_Clear(map);
   TypeMap_AddStringKey(map, "Type", "RemoveMapItemNotify");
   TypeMap_AddPointerKey(map, "MapItemAddress", map_item);
}

static void MapItemList_EventCallback(void * object, const TypeMap_T * event)
{
   MapItemList_T * list = object;
   MapItem_T map_item;

   if(TypeMap_IsStringEqual(event, "Type", "AddMapItemRequest") == 1)
   {
      map_item.item  = TypeMap_GetPointer(event, "Item");
      map_item.pos.x = TypeMap_GetInt(event, "X");
      map_item.pos.y = TypeMap_GetInt(event, "Y");
      map_item.pos.z = TypeMap_GetInt(event, "Z");
      MapItemList_Add(list, map_item.pos.x,
                            map_item.pos.y,
                            map_item.pos.z,
                            map_item.item);
   }

}

void MapItemList_Init(MapItemList_T * list)
{
   ManagerEvent_T * event_man;
   event_man = Resources_GetEventManager();

   ManagerEvent_RegisterCallback(event_man, list, MapItemList_EventCallback);
   ObjectList_Init(&list->mapitem_list, 0);
   RefCounterQueue_Init(&list->mem_queue);
}

void MapItemList_Destory(MapItemList_T * list)
{
   ManagerEvent_T * event_man;
   MapItem_T * item_rc;
   size_t i, count;
   count = ObjectList_Count(&list->mapitem_list);
   for(i = 0; i < count; i++)
   {
      item_rc = ObjectList_Get(&list->mapitem_list, i);
      MapItem_Destroy(item_rc);
      free(item_rc);
   }

   event_man = Resources_GetEventManager();

   ManagerEvent_UnregisterCallback(event_man, list);


   
   RefCounterQueue_Destroy(&list->mem_queue);
   ObjectList_Destory(&list->mapitem_list);
}

void MapItemList_Update(MapItemList_T * list, float seconds)
{
   MapItem_T * item_rc;
   size_t i, count;

   count = ObjectList_Count(&list->mapitem_list);
   for(i = 0; i < count; i++)
   {
      item_rc = ObjectList_Get(&list->mapitem_list, i);
   }

   while((item_rc = RefCounterQueue_Next(&list->mem_queue)) != NULL)
   {
      MapItem_Unlink(item_rc);
      MapItem_Destroy(item_rc);
      free(item_rc);
   }
}

void MapItemList_Add(MapItemList_T * list, int x, int y, int z, Item_T * item)
{
   MapItem_T * item_rc;
   ManagerEvent_T * event_man;
   TypeMap_T event;
   
   item_rc = malloc(sizeof(MapItem_T));
   MapItem_Init(item_rc, x, y, z, item);

   RefCounter_Keep(&item_rc->ref);

   ObjectList_AddAtEnd(&list->mapitem_list, item_rc);
   RefCounterQueue_Add(&list->mem_queue, item_rc, &item_rc->ref);

   event_man = Resources_GetEventManager();
   TypeMap_Init(&event);
   MapItemEvent_AddMapItemNotify_Init(&event, item_rc);
   ManagerEvent_SendEvent(event_man, &event);
   TypeMap_Destory(&event);
}

void MapItemList_Remove(MapItemList_T * list, Item_T * item)
{
   size_t i, count;
   MapItem_T * item_rc;
   int found, index;
   ManagerEvent_T * event_man;
   TypeMap_T event;

   found = 0;
   count = ObjectList_Count(&list->mapitem_list);
   for(i = 0; i < count; i++)
   {
      item_rc = ObjectList_Get(&list->mapitem_list, i);
      if(item_rc->item == item)
      {
         index = i;
         found = 1;
         break;
      }
   }
   if(found == 1)
   {
      RefCounter_Release(&item_rc->ref);
      ObjectList_RemoveFast(&list->mapitem_list, index);
      event_man = Resources_GetEventManager();
      TypeMap_Init(&event);
      MapItemEvent_RemoveMapItemNotify_Init(&event, item_rc);
      ManagerEvent_SendEvent(event_man, &event);
      TypeMap_Destory(&event);

   }
}


