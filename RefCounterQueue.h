#ifndef __REFCOUNTERQUEUE_H__
#define __REFCOUNTERQUEUE_H__
#include "RefCounter.h"
#include "ArrayList.h"

typedef struct RefCounterQueue_S RefCounterQueue_T;
struct RefCounterQueue_S
{
   ArrayList_T list;
   size_t last_index;
};

void RefCounterQueue_Init(RefCounterQueue_T * queue);
void RefCounterQueue_Destroy(RefCounterQueue_T * queue);

void RefCounterQueue_Add(RefCounterQueue_T * queue, void * memory, RefCounter_T * counter);

void * RefCounterQueue_Next(RefCounterQueue_T * queue);




#endif // __REFCOUNTERQUEUE_H__

