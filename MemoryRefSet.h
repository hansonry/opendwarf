#ifndef __MEMORYREFSET_H__
#define __MEMORYREFSET_H__
#include <stddef.h>
#include "ArrayList.h"

typedef struct MemoryRefSet_S MemoryRefSet_T;
typedef void (*MemoryRefSet_Freeer_T)(void * data);

struct MemoryRefSet_S
{
   size_t                element_size;
   MemoryRefSet_Freeer_T freer;
   ArrayList_T          memory_list;

};


void MemoryRefSet_Init(MemoryRefSet_T * mem, size_t element_size, MemoryRefSet_Freeer_T freer);
void MemoryRefSet_Destroy(MemoryRefSet_T * mem);


void * MemoryRefSet_Allocate(MemoryRefSet_T * mem);
void * MemoryRefSet_CopyAllocate(MemoryRefSet_T * mem, const void * data);
void * MemoryRefSet_ArrayAllocate(MemoryRefSet_T * mem, size_t count);

void MemoryRefSet_Keep(MemoryRefSet_T * mem, void * object);
void MemoryRefSet_Release(MemoryRefSet_T * mem, void * object);


void MemoryRefSet_CheckCounts(MemoryRefSet_T * mem);

#endif // __MEMORYREFSET_H__

