#ifndef __HEAPLIST_H__
#define __HEAPLIST_H__

#include <stddef.h>

#include "ArrayList.h"
typedef void (*HeapList_Callback_T)(void * object, void * data);
typedef struct HeapList_S HeapList_T;
struct HeapList_S
{
   size_t element_size;
   size_t elements_per_block;
   ArrayList_T block_list;
   ArrayList_T unused_memory;
   size_t count;
};

void   HeapList_Init(HeapList_T * list, size_t element_size, size_t elements_per_block);
void   HeapList_Destory(HeapList_T * list);

void * HeapList_Allocate(HeapList_T * list);
void   HeapList_Free(HeapList_T * list, void * mem);
void   HeapList_FreeAll(HeapList_T * list);

void   HeapList_CallAll(HeapList_T * list, HeapList_Callback_T callback, void * data);

size_t HeapList_GetCount(const HeapList_T * list);





#endif // __HEAPLIST_H__


