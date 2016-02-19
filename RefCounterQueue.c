#include "RefCounterQueue.h"

typedef struct RCQMem_S RCQMem_T;
 
struct RCQMem_S
{
   void         * memory;
   RefCounter_T * counter;
};


void RefCounterQueue_Init(RefCounterQueue_T * queue)
{
   ArrayList_Init(&queue->list, sizeof(RCQMem_T), 0);
   queue->last_index = 0;
}

void RefCounterQueue_Destroy(RefCounterQueue_T * queue)
{
   ArrayList_Destory(&queue->list);
}

void RefCounterQueue_Add(RefCounterQueue_T * queue, void * memory, RefCounter_T * counter)
{
   RCQMem_T mem;
   mem.memory  = memory;
   mem.counter = counter;
   ArrayList_CopyAdd(&queue->list, &mem, NULL);
}


void * RefCounterQueue_Next(RefCounterQueue_T * queue)
{
   size_t end_index;
   size_t i, count;
   RCQMem_T * m_list;
   void     * result;

   m_list = ArrayList_Get(&queue->list, &count, NULL);

   // Compute the last index
   if(queue->last_index == 0)
   {
      end_index = count - 1;
   }
   else
   {
      end_index = queue->last_index - 1;
   }

   i = queue->last_index;
   result = NULL;
   while(i != end_index)
   {
      if(RefCounter_ShouldDelete(m_list[i].counter))
      {
         result = m_list[i].memory;
         ArrayList_Remove(&queue->list, i);
         i = end_index; // Exit Loop
      }
      i ++;
      if(i >= count)
      {
         i = 0;
      }
   }
   
   return result;
}

