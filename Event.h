#ifndef __EVENT_H__
#define __EVENT_H__

typedef struct Event_S     Event_T;
typedef enum   EventType_E EventType_T;

enum EventType_E
{
   e_ET_NULL,
   e_ET_CreateItem,
   e_ET_Last
};

struct Event_S
{
   EventType_T   type;
   void        * data;
};

#endif // __EVENT_H__

