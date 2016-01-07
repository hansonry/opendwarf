#include "ManagerEvent.h"

typedef struct EventReg_S EventReg_T;

struct EventReg_S
{
   void              * object;
   EventCallback_T     callback;
   const EventType_T * type_filter;
   size_t              type_filter_count;
};

void ManagerEvent_Init(ManagerEvent_T * man)
{
   ListMemory_Init(&man->event_reg, sizeof(EventReg_T), 0);
}

void ManagerEvent_Destroy(ManagerEvent_T * man)
{
   ListMemory_Destory(&man->event_reg);
}


void ManagerEvent_SentEvent(ManagerEvent_T * man, const Event_T * event)
{
   EventReg_T * list;
   size_t count, i, k;
   int found;

   list = ListMemory_Get(&man->event_reg, &count, NULL);
   for(i = 0; i < count; i ++)
   {
      found = 0;
      for(k = 0; k < list[i].type_filter_count; k++)
      {
         if(list[i].type_filter[k] == event->type)
         {
            found = 1;
         }
      }

      if(found == 1)
      {
         list[i].callback(list[i].object, event);
      }
   }
}


void ManagerEvent_RegisterCallback(ManagerEvent_T * man, void * object, EventCallback_T callback, const EventType_T * types, size_t count)
{
   EventReg_T reg;
   reg.object            = object;
   reg.callback          = callback;
   reg.type_filter       = types;
   reg.type_filter_count = count;

   ListMemory_CopyAlloc(&man->event_reg, &reg, NULL);
}

void ManagerEvent_UnregisterCallback(ManagerEvent_T * man, void * object)
{
   EventReg_T * list;
   size_t count, i;

   list = ListMemory_Get(&man->event_reg, &count, NULL);
   for(i = 0; i < count; i ++)
   {
      if(list[i].object == object)
      {
         ListMemory_FreeNow(&man->event_reg, i);
         break;
      }
   }
}

