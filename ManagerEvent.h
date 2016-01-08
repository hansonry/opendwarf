#ifndef __MANAGEREVENT_H__
#define __MANAGEREVENT_H__

#include "ListMemory.h"
#include "TypeMap.h"

typedef struct ManagerEvent_S ManagerEvent_T;
typedef void (*EventCallback_T)(void * object, const TypeMap_T * event);

struct ManagerEvent_S
{
   ListMemory_T event_reg;
   TypeMap_T event;
};


void ManagerEvent_Init(ManagerEvent_T * man);
void ManagerEvent_Destroy(ManagerEvent_T * man);

void ManagerEvent_SendEvent(ManagerEvent_T * man, const TypeMap_T * event);

void ManagerEvent_RegisterCallback(ManagerEvent_T * man, void * object, EventCallback_T callback);

void ManagerEvent_UnregisterCallback(ManagerEvent_T * man, void * object);

TypeMap_T * ManagerEvent_GetEvent(ManagerEvent_T * man);

#endif // __MANAGEREVENT_H__

