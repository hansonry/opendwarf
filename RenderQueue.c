#include "RenderQueue.h"

void RenderQueue_Init(RenderQueue_T * queue, size_t object_size)
{
   PriorityQueue_Init(&queue->queue, object_size);
}

void RenderQueue_Destory(RenderQueue_T * queue)
{
   PriorityQueue_Destory(&queue->queue);
}

void RenderQueue_Add(RenderQueue_T * queue, void * object)
{
   PriorityQueue_Insert(&queue->queue, object, 0);
}

void RenderQueue_Peek(RenderQueue_T * queue, void * object_out)
{
   (void)PriorityQueue_Peek(&queue->queue, object_out);
}

int RenderQueue_Pop(RenderQueue_T * queue, void * object_out)
{
   return PriorityQueue_Pop(&queue->queue, object_out);
}

void RenderQueue_Flush(RenderQueue_T * queue)
{
   PriorityQueue_Clear(&queue->queue);
}

int RenderQueue_HasMore(RenderQueue_T * queue)
{
   return PriorityQueue_Count(&queue->queue) > 0;
}

