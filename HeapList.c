#include "HeapList.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_ELEMENTS_PER_BLOCK 32
#define GET_INDEX(list, memory, index) (&(((byte_t *)(memory))[(index) * (list)->element_size]))

typedef unsigned char byte_t;
typedef struct HeapList_Block_S HeapList_Block_T;
struct HeapList_Block_S
{
   byte_t * memory;
   size_t   size;

};

void   HeapList_Init(HeapList_T * list, size_t element_size, size_t elements_per_block)
{
   list->element_size = element_size;
   list->count        = 0;
   if(elements_per_block == 0)
   {
      list->elements_per_block = DEFAULT_ELEMENTS_PER_BLOCK;
   }
   else
   {
      list->elements_per_block = elements_per_block;
   }
   ArrayList_Init(&list->block_list, sizeof(HeapList_Block_T), 0);
   ArrayList_Init(&list->unused_memory, sizeof(byte_t *), 0);
}

void   HeapList_Destory(HeapList_T * list)
{
   size_t i, count;
   HeapList_Block_T * block;


   block = ArrayList_Get(&list->block_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      free(block[i].memory);
   }

   ArrayList_Destory(&list->block_list);
   ArrayList_Destory(&list->unused_memory);
}

static void HeapList_CreateNewBlock(HeapList_T * list)
{
   HeapList_Block_T block;
   size_t i;
   byte_t * loop;
   block.size   = list->elements_per_block;
   block.memory = malloc(list->element_size * list->elements_per_block);

   // Add all empty address to list
   loop = block.memory;
   for(i = 0; i < block.size; i ++)
   {
      ArrayList_CopyAdd(&list->unused_memory, &loop, NULL);
      loop += list->element_size;
   }

   ArrayList_CopyAdd(&list->block_list, &block, NULL);
}

void * HeapList_Allocate(HeapList_T * list)
{
   byte_t ** unused_list;
   byte_t * mem;
   size_t count;

   unused_list = ArrayList_Get(&list->unused_memory, &count, NULL);
   if(count == 0)
   {
      HeapList_CreateNewBlock(list);
      unused_list = ArrayList_Get(&list->unused_memory, &count, NULL);
   }

   mem = unused_list[0];
   ArrayList_Remove(&list->unused_memory, 0);
   list->count ++;

   return mem;
}

static int HeapList_OwnsMemory(HeapList_T * list, void * mem)
{
   size_t i, k, count;
   byte_t * loop;
   HeapList_Block_T * block_list;
   int found;
   found = 0;

   block_list = ArrayList_Get(&list->block_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      loop = block_list[i].memory;
      for(k = 0; k < block_list[i].size; k++)
      {
         if(loop == mem)
         {
            found = 1;
            break;
         }
         loop = loop + list->element_size;
      }
      if(found == 1)
      {
         break;
      }

   }

   return found;

}

void   HeapList_Free(HeapList_T * list, void * mem)
{
   int found;
   found = HeapList_OwnsMemory(list, mem);
   if(found == 1)
   {
      ArrayList_CopyAdd(&list->unused_memory, &mem, NULL);
      list->count --;
   }
   else
   {
      printf("Error: HeapList_Free: HeapList %p does not own memory: %p\n", list, mem);
   }
}

void   HeapList_FreeAll(HeapList_T * list)
{
   size_t i, k, count;
   byte_t * loop;
   HeapList_Block_T * block_list;
   ArrayList_Clear(&list->unused_memory);

   block_list = ArrayList_Get(&list->block_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      loop = block_list[i].memory;
      for(k = 0; k < block_list[i].size; k++)
      {
         ArrayList_CopyAdd(&list->unused_memory, &loop, NULL);
         loop = loop + list->element_size;
      }

   }
   list->count = 0;

}

void   HeapList_CallAll(HeapList_T * list, HeapList_Callback_T callback, void * data)
{
   size_t i, k, count;
   byte_t * loop;
   HeapList_Block_T * block_list;

   block_list = ArrayList_Get(&list->block_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      loop = block_list[i].memory;
      for(k = 0; k < block_list[i].size; k++)
      {
         callback(loop, data);
         loop = loop + list->element_size;
      }

   }
}


size_t HeapList_GetCount(const HeapList_T * list)
{
   return list->count;
}

