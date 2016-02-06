#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__
#include <stddef.h>
typedef struct PriorityQueue_S     PriorityQueue_T;
typedef struct PriorityQueueLink_S PriorityQueueLink_T;


struct PriorityQueue_S
{
   PriorityQueueLink_T * root;
   size_t                object_size;
   size_t                count;
};

void   PriorityQueue_Init(PriorityQueue_T * queue, size_t object_size);
void   PriorityQueue_Destory(PriorityQueue_T * queue);

void   PriorityQueue_Insert(PriorityQueue_T * queue, const void * object_in, int priority);
void   PriorityQueue_InsertMax(PriorityQueue_T * queue, const void * object_in);
void   PriorityQueue_InsertMin(PriorityQueue_T * queue, const void * object_in);

int    PriorityQueue_Peek(const PriorityQueue_T * queue, void * object_out);
int    PriorityQueue_Pop(PriorityQueue_T * queue, void * object_out);

size_t PriorityQueue_Count(const PriorityQueue_T * queue);

void   PriorityQueue_Clear(PriorityQueue_T * queue);


#endif // __PRIORITYQUEUE_H__

