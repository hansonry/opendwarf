#ifndef __LISTMEMORY_H__
#define __LISTMEMORY_H__

#include <stddef.h>

typedef struct ListMemory_S        ListMemory_T;
typedef struct ListMemoryDelLink_S ListMemoryDelLink_T;
struct ListMemory_S
{
   void * memory;
   size_t element_size;
   size_t element_count;
   size_t memory_size;
   size_t grow_by;

   ListMemoryDelLink_T * root;

};

void ListMemory_Init(ListMemory_T * list, size_t element_size, size_t grow_by);
void ListMemory_Destory(ListMemory_T * list);


void * ListMemory_Allocate(ListMemory_T * list, size_t * index);
void ListMemory_CopyAlloc(ListMemory_T * list, const void * mem, size_t * index);
void * ListMemory_GetIndex(ListMemory_T * list, size_t index);
void ListMemory_FreeNow(ListMemory_T * list, size_t index);
void ListMemory_FreeLater(ListMemory_T * list, size_t index);
void ListMemory_FlushFree(ListMemory_T * list);

void * ListMemory_Get(ListMemory_T * list, size_t * count, size_t * element_size);

void * ListMemory_GetCopy(ListMemory_T * list, size_t * count, size_t * element_size);



#endif // __LISTMEMORY_H__

