#include "PriorityQueue.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef unsigned char byte_t;

#define GETADDY(mem) (&((byte_t*)(mem))[sizeof(PriorityQueueLink_T)])

struct PriorityQueueLink_S
{
   PriorityQueueLink_T * next;
   int priority;
};

void   PriorityQueue_Init(PriorityQueue_T * queue, size_t object_size)
{
   queue->root        = NULL;
   queue->object_size = object_size;
   queue->count       = 0;
}

void   PriorityQueue_Destory(PriorityQueue_T * queue)
{
   PriorityQueue_Clear(queue);
}

static PriorityQueueLink_T * PriorityQueue_NewLink(PriorityQueue_T * queue, const void * object_in, int priority)
{
   PriorityQueueLink_T * link;
   link = malloc(sizeof(PriorityQueueLink_T) + queue->object_size);
   memcpy(GETADDY(link), object_in, queue->object_size);
   link->priority = priority;
   link->next = NULL;
   return link;
}

void   PriorityQueue_Insert(PriorityQueue_T * queue, const void * object_in, int priority)
{
   PriorityQueueLink_T * loop, * prev, * link;
   link = PriorityQueue_NewLink(queue, object_in, priority);

   if(queue->root = NULL)
   {
      queue->root = link;
      queue->count = 1;
   }
   else
   {
      prev = NULL;
      loop = queue->root;
      while(loop != NULL)
      {
         if(link->priority > loop->priority) // Smallest will be last
         {
            if(prev == NULL)
            {
               link->next = queue->root;
               queue->root = link;
            }
            else
            {
               link->next = loop;
               prev->next = link;
            }

            loop = NULL;
         }
         else if(loop->next == NULL)
         {
            loop->next = link;
            loop = NULL;
         }
         else
         {
            // March Forward
            prev = loop;
            loop = loop->next;
         }
      }
      queue->count ++;
   }



}

void   PriorityQueue_InsertMax(PriorityQueue_T * queue, const void * object_in)
{
   PriorityQueue_Insert(queue, object_in, INT_MAX);
}

void   PriorityQueue_InsertMin(PriorityQueue_T * queue, const void * object_in)
{
   PriorityQueue_Insert(queue, object_in, INT_MIN);
}

int    PriorityQueue_Peek(const PriorityQueue_T * queue, void * object_out)
{
   int result;
   if(queue->count > 0)
   {
      if(object_out != NULL)
      {
         memcpy(object_out, GETADDY(queue->root), queue->object_size); 
      }
      result = 1;
   }
   else
   {
      result = 0;
   }

   return result;
}

int    PriorityQueue_Pop(PriorityQueue_T * queue, void * object_out)
{
   int result;
   PriorityQueueLink_T * link;
   if(queue->count > 0)
   {
      if(object_out != NULL)
      {
         memcpy(object_out, GETADDY(queue->root), queue->object_size); 
      }

      link = queue->root;
      queue->root = queue->root->next;
      free(link);
      queue->count --;
      result = 1;
   }
   else
   {
      result = 0;
   }


   return result;
}


size_t PriorityQueue_Count(const PriorityQueue_T * queue)
{
   return queue->count;
}

void   PriorityQueue_Clear(PriorityQueue_T * queue)
{
   PriorityQueueLink_T * loop, * temp;


   loop = queue->root;
   while(loop != NULL)
   {
      temp = loop;
      loop = loop->next;

      free(temp);
   }
   queue->root = NULL;

   queue->count = 0;
}

