#include "ArrayList.h"

#include <stdlib.h>
#include <string.h>

typedef unsigned char byte_t;
struct ArrayListDelLink_S
{
   size_t index;
   ArrayListDelLink_T * next;
};

#define ADDY(list, offset) (&(((byte_t *)(list->memory))[(list->element_size) * (offset)]))

#define GROW_BY 16

void ArrayList_Init(ArrayList_T * list, size_t element_size, size_t grow_by)
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

}

void ArrayList_Destory(ArrayList_T * list)
{
   free(list->memory);
}



void * ArrayList_Add(ArrayList_T * list, size_t * index)
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
void ArrayList_CopyAdd(ArrayList_T * list, const void * mem, size_t * index)
{
   void * new_mem;
   new_mem = ArrayList_Add(list, index);
   memcpy(new_mem, mem, list->element_size);
}

void * ArrayList_GetIndex(ArrayList_T * list, size_t index)
{
   return ADDY(list, index);
}

static void ArrayList_RemoveIndex(ArrayList_T * list, size_t index)
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

void ArrayList_Remove(ArrayList_T * list, size_t index)
{
   ArrayList_RemoveIndex(list, index);
}

void ArrayList_Clear(ArrayList_T * list)
{
   list->element_count = 0;
}

void * ArrayList_Get(ArrayList_T * list, size_t * count, size_t * element_size)
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

void * ArrayList_GetCopy(ArrayList_T * list, size_t * count, size_t * element_size)
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

void ArrayList_SwapLists(ArrayList_T * list1, ArrayList_T * list2)
{
   ArrayList_T temp;
   memcpy(&temp, list1, sizeof(ArrayList_T));
   memcpy(list1, list2, sizeof(ArrayList_T));
   memcpy(list2, &temp, sizeof(ArrayList_T));

}

