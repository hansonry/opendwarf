#ifndef __LISTMEMORY_H__
#define __LISTMEMORY_H__

#include <stddef.h>

typedef struct ArrayList_S        ArrayList_T;
typedef struct ArrayListDelLink_S ArrayListDelLink_T;
struct ArrayList_S
{
   void * memory;
   size_t element_size;
   size_t element_count;
   size_t memory_size;
   size_t grow_by;
};

void ArrayList_Init(ArrayList_T * list, size_t element_size, size_t grow_by);
void ArrayList_Destory(ArrayList_T * list);


void * ArrayList_Add(ArrayList_T * list, size_t * index);
void ArrayList_CopyAdd(ArrayList_T * list, const void * mem, size_t * index);
void * ArrayList_GetIndex(ArrayList_T * list, size_t index);
void ArrayList_Remove(ArrayList_T * list, size_t index);
void ArrayList_Clear(ArrayList_T * list);
void ArrayList_SwapLists(ArrayList_T * list1, ArrayList_T * list2);

void * ArrayList_Get(ArrayList_T * list, size_t * count, size_t * element_size);

void * ArrayList_GetCopy(ArrayList_T * list, size_t * count, size_t * element_size);



#endif // __LISTMEMORY_H__

