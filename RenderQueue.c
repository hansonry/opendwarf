#include "RenderQueue.h"
#include <stdlib.h>

void RenderQueue_Init(RenderQueue_T * queue)
{
   queue->root  = NULL;
   queue->count = 0;
}

void RenderQueue_Destory(RenderQueue_T * queue)
{
   RenderQueue_Flush(queue);
}

static RenderQueueLink_T * RenderQueueLink_CreateLink(Shader_T * shader,
                                                      void     * shader_state,
                                                      int        is_transparent)
{
   RenderQueueLink_T * link;
   link = malloc(sizeof(RenderQueueLink_T));
   link->next         = NULL;
   link->shader       = shader;
   link->shader_state = shader_state;
   if(is_transparent)
   {
      link->priority = 1;
   }
   else
   {
      link->priority = 0;
   }
   return link;
}

void RenderQueue_Add(RenderQueue_T * queue, Shader_T * shader, 
                                            void     * shader_state,
                                            int        is_transparent)
{
   RenderQueueLink_T * link, * prev, * loop;
   int is_placed;
   link = RenderQueueLink_CreateLink(shader, shader_state, is_transparent);

   loop = queue->root;
   prev = NULL;
   is_placed = 0;

   while(loop != NULL && is_placed == 0)
   {
      if(link->priority < loop->priority)
      {
         if(prev == NULL)
         {
            queue->root = link;
         }
         else
         {
            prev->next = link;
         }
         link->next = loop;
         is_placed  = 1;
      }

      prev = loop;
      loop = loop->next;
   }

   if(is_placed == 0)
   {
      if(prev == NULL)
      {
         // Add to root
         queue->root = link;
      }
      else
      {
         prev->next = link;
      }
   }
   queue->count ++;
}


void RenderQueue_Flush(RenderQueue_T * queue)
{
   RenderQueueLink_T * loop, * temp;

   loop = queue->root;
   while(loop != NULL)
   {
      temp = loop;
      loop = loop->next;
      free(temp);
   }
   queue->count = 0;
   queue->root = NULL;
}


void RenderQueue_Render(RenderQueue_T * queue)
{
   RenderQueueLink_T * loop, * prev;
   Shader_T * s_next, *  s_prev;
   prev = NULL;
   loop = queue->root;
  
   while(loop != NULL)
   {
      if(prev == NULL)
      {
         s_prev = NULL;
      }
      else
      {
         s_prev = prev->shader;
      }

      if(loop->next == NULL)
      {
         s_next = NULL;
      }
      else
      {
         s_next = loop->next->shader;
      }

      Shader_Render(loop->shader, loop->shader_state, s_prev, s_next);

      prev = loop;
      loop = loop->next;
   }

   RenderQueue_Flush(queue);
}

