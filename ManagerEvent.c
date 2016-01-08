#include "ManagerEvent.h"

typedef struct EventReg_S EventReg_T;
typedef unsigned char UInt8_T;

struct EventReg_S
{
   void              * object;
   EventCallback_T     callback;
};

void ManagerEvent_Init(ManagerEvent_T * man)
{
   ListMemory_Init(&man->event_reg, sizeof(EventReg_T), 0);
   TypeMap_Init(&man->event);
}

void ManagerEvent_Destroy(ManagerEvent_T * man)
{
   ListMemory_Destory(&man->event_reg);
   TypeMap_Destory(&man->event);
}


void ManagerEvent_SendEvent(ManagerEvent_T * man, const TypeMap_T * event)
{
   EventReg_T * list;
   size_t count, i, k;

   list = ListMemory_Get(&man->event_reg, &count, NULL);
   for(i = 0; i < count; i ++)
   {
      list[i].callback(list[i].object, event);
   }
}


void ManagerEvent_RegisterCallback(ManagerEvent_T * man, void * object, EventCallback_T callback)
{
   EventReg_T reg;
   reg.object            = object;
   reg.callback          = callback;

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

TypeMap_T * ManagerEvent_GetEvent(ManagerEvent_T * man)
{
   return &man->event;
}

