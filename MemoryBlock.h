#ifndef __MEMORYBLOCK_H__
#define __MEMORYBLOCK_H__
#include <stddef.h>
#include "ArrayList.h"

typedef struct MemoryBlock_S      MemoryBlock_T;
typedef struct MemoryBlockChunk_S MemoryBlockChunk_T;

struct MemoryBlockChunk_S
{
   void * memory;
   size_t size;
   MemoryBlockChunk_T * next;
};

struct MemoryBlock_S
{
   size_t element_size;
   size_t grow_by;
   size_t count;
   size_t max_count;
   size_t main_chunk_used_count;
   MemoryBlockChunk_T main_chunk;
   MemoryBlockChunk_T * root;
   ArrayList_T record_list;

};

void   MemoryBlock_Init(MemoryBlock_T * block, size_t element_size, 
                                               size_t init_count, 
                                               size_t grow_by);

void   MemoryBlock_Destroy(MemoryBlock_T * block);

void * MemoryBlock_Allocate(MemoryBlock_T * block);
void   MemoryBlock_Free(MemoryBlock_T * block, void * memory);

void   MemoryBlock_FreeAll(MemoryBlock_T * block);

void   MemoryBlock_ShrinkWrap(MemoryBlock_T * block);

#endif // __MEMORYBLOCK_H__

