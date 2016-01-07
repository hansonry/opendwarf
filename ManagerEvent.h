#ifndef __MANAGEREVENT_H__
#define __MANAGEREVENT_H__

#include <stddef.h>
#include "ListMemory.h"
#include "Event.h"

typedef struct ManagerEvent_S ManagerEvent_T;
typedef void (*EventCallback_T)(void * object, const Event_T * event);

struct ManagerEvent_S
{
   ListMemory_T event_reg;
};


void ManagerEvent_Init(ManagerEvent_T * man);
void ManagerEvent_Destroy(ManagerEvent_T * man);

void ManagerEvent_SendEvent(ManagerEvent_T * man, const Event_T * event);

void ManagerEvent_RegisterCallback(ManagerEvent_T * man, void * object, EventCallback_T callback, const EventType_T * types, size_t count);

void ManagerEvent_UnregisterCallback(ManagerEvent_T * man, void * object);


#endif // __MANAGEREVENT_H__

