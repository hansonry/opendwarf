#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__

#include <stddef.h>

typedef struct ObjectList_S ObjectList_T;
struct ObjectList_S
{
   void   ** list;
   size_t    size;
   size_t    count;
};

void ObjectList_Init(ObjectList_T * list);
void ObjectList_Destory(ObjectList_T * list);

void ObjectList_Add(ObjectList_T * list, void * obj);

void * ObjectList_Get(ObjectList_T * list, size_t * count);

void ObjectList_RemoveAll(ObjectList_T * list);


#endif // __OBJECTLIST_H__

