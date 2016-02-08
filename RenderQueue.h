#ifndef __RENDERQUEUE_H__
#define __RENDERQUEUE_H__
#include "PriorityQueue.h"

typedef struct RenderQueue_S RenderQueue_T;
struct RenderQueue_S
{
   PriorityQueue_T queue;
  
};


void RenderQueue_Init(RenderQueue_T * queue, size_t object_size);
void RenderQueue_Destory(RenderQueue_T * queue);

void RenderQueue_Add(RenderQueue_T * queue, void * object);

void RenderQueue_Peek(RenderQueue_T * queue, void * object_out);
int RenderQueue_Pop(RenderQueue_T * queue, void * object_out);

void RenderQueue_Flush(RenderQueue_T * queue);

int RenderQueue_HasMore(RenderQueue_T * queue);



#endif // __RENDERQUEUE_H__


