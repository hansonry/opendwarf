#include "MemoryBlock.h"
#include <stdlib.h>
typedef unsigned char byte_t;
typedef struct MBRecord_S MBRecord_T;

struct MBRecord_S
{
   void   * memory;
   byte_t   flags;
};


#define BYTE_OFFSET(mem, index) (&(((byte_t *)(mem))[(index)]))
#define DEFAULT_GROWBY 16
#define FLAG_ISUSED      0x01
#define FLAG_ISMAINCHUNK 0x02

#define SETFLAG(field, flag)   (field) |= (flag)
#define CLEARFLAG(field, flag) (field) &= ~(flag)
#define CHECKFLAG(field, flag) ((field) & (flag) == (flag))


static void MemoryBlock_AddMemoryChunk(MemoryBlock_T * block, MemoryBlockChunk_T * chunk, size_t * index, byte_t flags)
{
   size_t i;
   size_t byte_index;
   MBRecord_T record;
   byte_index = 0;
   for(i = 0; i < chunk->size; i++)
   {
      record.flags = flags;
      CLEARFLAG(record.flags, FLAG_ISUSED);
      
      record.memory = BYTE_OFFSET(chunk->memory, byte_index);
      ArrayList_CopyAdd(&block->record_list, &record, index);

      byte_index += block->element_size;
   }
}

static void MemoryBlock_CheckForResize(MemoryBlock_T * block)
{
   size_t new_size;
   size_t count, i;
   MBRecord_T * list;

   if((block->main_chunk_used_count == 0) && 
      (block->main_chunk.size < block->max_count))
   {
      new_size = block->max_count + block->grow_by;
      
      block->main_chunk.memory = realloc(block->main_chunk.memory, 
                                         block->element_size * new_size);
      block->main_chunk.size   = new_size;

      list = ArrayList_Get(&block->record_list, &count, NULL);
      for(i = count - 1; i < count; i--)
      {
         if(CHECKFLAG(list[i].flags, FLAG_ISMAINCHUNK))
         {
            ArrayList_Remove(&block->record_list, i);
         }
      }
      MemoryBlock_AddMemoryChunk(block, &block->main_chunk, NULL, FLAG_ISMAINCHUNK);
   }
}

void   MemoryBlock_Init(MemoryBlock_T * block, size_t element_size, 
                                               size_t init_count, 
                                               size_t grow_by)
{
   block->element_size = element_size;
   if(grow_by == 0)
   {
      block->grow_by = DEFAULT_GROWBY;
   }
   else
   {
      block->grow_by = grow_by;
   }
   block->max_count = 0;
   block->count = 0;

   ArrayList_Init(&block->record_list, sizeof(MBRecord_T), 0);

   block->main_chunk.size       = init_count;
   block->main_chunk.memory     = malloc(block->element_size * block->main_chunk.size);
   block->main_chunk.next       = NULL;
   block->main_chunk_used_count = 0;
   block->root                  = NULL;

   MemoryBlock_AddMemoryChunk(block, &block->main_chunk, NULL, FLAG_ISMAINCHUNK);

}



void   MemoryBlock_Destroy(MemoryBlock_T * block)
{
   MemoryBlockChunk_T * loop, * temp;

   ArrayList_Destory(&block->record_list);
   free(block->main_chunk.memory);

   loop = block->root;
   while(loop != NULL)
   {
      temp = loop;
      loop = loop->next;

      free(temp->memory);
      free(temp);
   }


}

static MBRecord_T * MemoryBlock_GetFreeRecord(MemoryBlock_T * block)
{
   MBRecord_T * result;
   MBRecord_T * list;
   MemoryBlockChunk_T * new_link;
   size_t count, i, index;

   result = NULL;
   list = ArrayList_Get(&block->record_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(!CHECKFLAG(list[i].flags, FLAG_ISUSED))
      {
         result = &list[i];
         break;
      }
   }

   if(result == NULL)
   {
      // Out of memory so we need a new Chunk
      new_link = malloc(sizeof(MemoryBlockChunk_T));
      new_link->next = block->root;
      block->root = new_link;
      new_link->size = block->grow_by;
      new_link->memory = malloc(new_link->size * block->element_size);
      MemoryBlock_AddMemoryChunk(block, new_link, &index, 0);
      list = ArrayList_Get(&block->record_list, NULL, NULL);
      result = &list[index];
   }


   return result;
}

void * MemoryBlock_Allocate(MemoryBlock_T * block)
{
   MBRecord_T * record;
   record = MemoryBlock_GetFreeRecord(block);
   SETFLAG(record->flags, FLAG_ISUSED);
   block->count ++;

   if(block->count > block->max_count)
   {
      block->max_count = block->count;
   }

   if(CHECKFLAG(record->flags, FLAG_ISMAINCHUNK))
   {
      block->main_chunk_used_count ++;
   }
   return record->memory;
}

static MBRecord_T * MemoryBlock_FindRecordWithMemory(MemoryBlock_T * block, void * memory)
{
   MBRecord_T * result;
   MBRecord_T * list;
   MemoryBlockChunk_T * new_link;
   size_t count, i, index;

   result = NULL;
   list = ArrayList_Get(&block->record_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(list[i].memory == memory)
      {
         result = &list[i];
         break;
      }
   }

   return result;
}

void   MemoryBlock_Free(MemoryBlock_T * block, void * memory)
{
   MBRecord_T * record;
   record = MemoryBlock_FindRecordWithMemory(block, memory);
   if(record != NULL)
   {
      CLEARFLAG(record->flags, FLAG_ISUSED);
      block->count --;
      if(CHECKFLAG(record->flags, FLAG_ISMAINCHUNK))
      {
         block->main_chunk_used_count --;
      }
      MemoryBlock_CheckForResize(block);
   }
}

void   MemoryBlock_FreeAll(MemoryBlock_T * block)
{
   MBRecord_T * list;
   size_t count, i;

   list = ArrayList_Get(&block->record_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      CLEARFLAG(list[i].flags, FLAG_ISUSED);
   }
   block->count = 0;
   block->main_chunk_used_count = 0;
   MemoryBlock_CheckForResize(block);
}

void   MemoryBlock_ShrinkWrap(MemoryBlock_T * block)
{
   block->main_chunk_used_count = block->count;
   MemoryBlock_CheckForResize(block);
}


