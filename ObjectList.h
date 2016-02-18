#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__

#include <stddef.h>

typedef struct ObjectList_S     ObjectList_T;

struct ObjectList_S
{
   void   ** list;
   size_t    size;
   size_t    count;
   size_t    grow_by;
};


void ObjectList_Init(ObjectList_T * list, size_t grow_by);
void ObjectList_Destory(ObjectList_T * list);

void ObjectList_AddAtEnd(ObjectList_T * list, void * object);
void ObjectList_InsertBefore(ObjectList_T * list, size_t index, void * object);
void ObjectList_InsertAfter(ObjectList_T * list, size_t index, void * object);
void ObjectList_RemoveFast(ObjectList_T * list, size_t index);
void ObjectList_RemoveOrdered(ObjectList_T * list, size_t index);

size_t ObjectList_Count(const ObjectList_T * list);
void * ObjectList_Get(const ObjectList_T * list, size_t index);


void ObjectList_RemoveAll(ObjectList_T * list);


#endif // __OBJECTLIST_H__

