#include "ListMemory.h"

#include <stdlib.h>
#include <string.h>

typedef unsigned char byte_t;
struct ListMemoryDelLink_S
{
   size_t index;
   ListMemoryDelLink_T * next;
};

#define ADDY(list, offset) (&(((byte_t *)(list->memory))[(list->element_size) * (offset)]))

#define GROW_BY 16

void ListMemory_Init(ListMemory_T * list, size_t element_size, size_t grow_by)
{
   size_t new_size;
   list->element_size = element_size;
   if(grow_by == 0)
   {
      list->grow_by = GROW_BY;
   }
   else
   {
      list->grow_by = grow_by;
   }

   list->element_count = 0;
   new_size = list->grow_by;
   list->memory = malloc(list->element_size * new_size);
   list->memory_size = new_size;
   list->root = NULL;

}

void ListMemory_Destory(ListMemory_T * list)
{
   ListMemoryDelLink_T * link, * loop;
   loop = list->root;
   while(loop != NULL)
   {
      link = loop;
      loop = loop->next;
      free(link);
   }
   free(list->memory);
}



void * ListMemory_Allocate(ListMemory_T * list, size_t * index)
{
   byte_t * mem;
   size_t new_size;

   if(list->element_count >= list->memory_size)
   {
      new_size = list->element_count + list->grow_by;
      list->memory = realloc(list->memory, list->element_size * new_size);
      list->memory_size = new_size;
   }

   if(index != NULL)
   {
      (*index) = list->element_count;
   }

   mem = ADDY(list, list->element_count);
   list->element_count++;

   return mem;
}
void ListMemory_CopyAlloc(ListMemory_T * list, const void * mem, size_t * index)
{
   void * new_mem;
   new_mem = ListMemory_Allocate(list, index);
   memcpy(new_mem, mem, list->element_size);
}

void * ListMemory_GetIndex(ListMemory_T * list, size_t index)
{
   return ADDY(list, index);
}

static void ListMemory_RemoveIndex(ListMemory_T * list, size_t index)
{
   byte_t * mem_from, * mem_to;
   if(index < list->element_count - 1)
   {
      mem_to = ADDY(list, index);
      mem_from = ADDY(list, list->element_count - 1);
      memcpy(mem_to, mem_from, list->element_size);
   }
   list->element_count --;
}

void ListMemory_FreeNow(ListMemory_T * list, size_t index)
{
   ListMemory_RemoveIndex(list, index);
}

void ListMemory_FreeLater(ListMemory_T * list, size_t index)
{
   ListMemoryDelLink_T * link, * loop, *current;
   int is_good;

   // Remove Duplicates
   loop = list->root;
   is_good = 1;
   while(loop != NULL)
   {
      if(loop->index == index)
      {
         loop = NULL;
         is_good = 0;
      }
      else
      {
         loop = loop->next;
      }
   }

   if(is_good == 1)
   {

      // Create link;
      link = malloc(sizeof(ListMemoryDelLink_T));
      link->next = NULL;
      link->index = index;


      // Put into sorted list
      if(list->root == NULL)
      {
         list->root = link;
      }
      else if(list->root->index < link->index)
      {
         link->next = list->root;
         list->root = link;
      }
      else
      {
         loop = list->root;
         while(loop != NULL)
         {
            current = loop;
            loop = loop->next;

            if(current->next == NULL ||
               current->next->index < link->index)
            {
               link->next = current->next;
               current->next = link;
               loop = NULL; // Exit loop
            }
         }
      }
   }

}

void ListMemory_FlushFree(ListMemory_T * list)
{
   ListMemoryDelLink_T * link, * loop;
   loop = list->root;
   while(loop != NULL)
   {
      link = loop;
      loop = loop->next;
      ListMemory_RemoveIndex(list, link->index);
      free(link);
   }
}

void ListMemory_Clear(ListMemory_T * list)
{
   list->element_count = 0;
}

void * ListMemory_Get(ListMemory_T * list, size_t * count, size_t * element_size)
{
   if(count != NULL)
   {
      (*count) = list->element_count;
   }
   if(element_size != NULL)
   {
      (*element_size) = list->element_size;
   }
   return list->memory;
}

void * ListMemory_GetCopy(ListMemory_T * list, size_t * count, size_t * element_size)
{
   void * mem;
   size_t size;
   if(count != NULL)
   {
      (*count) = list->element_count;
   }
   if(element_size != NULL)
   {
      (*element_size) = list->element_size;
   }
   size = list->element_count * list->element_size;

   mem = malloc(size);
   memcpy(mem, list->memory, size);
   return mem;
}

