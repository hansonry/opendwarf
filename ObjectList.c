#include "ObjectList.h"
#include <stdlib.h>

#define DEFAULT_GROWBY 16

void ObjectList_Init(ObjectList_T * list, size_t grow_by)
{
   size_t new_size;
   if(grow_by == 0)
   {
      list->grow_by = DEFAULT_GROWBY;
   }
   else
   {
      list->grow_by = grow_by;
   }

   list->count = 0;

   new_size = list->grow_by;
   list->list = malloc(sizeof(void*) * new_size);
   list->size = new_size;
}

void ObjectList_Destory(ObjectList_T * list)
{
   free(list->list);
   list->list  = NULL;
   list->count = 0;
   list->size  = 0;
}

static void ObjectList_MakeRoomFor(ObjectList_T * list, size_t size)
{
   size_t new_size;
   if(list->size < size)
   {
      new_size   = size + list->grow_by;
      list->list = realloc(list->list, sizeof(void*) * new_size);
      list->size = new_size;
   }
}

void ObjectList_AddAtEnd(ObjectList_T * list, void * object)
{
   size_t new_count;
   new_count = list->count + 1;
   ObjectList_MakeRoomFor(list, new_count);
   list->list[list->count] = object;
   list->count = new_count;
}

static void ObjectList_InsertAt(ObjectList_T * list, size_t index, void * object)
{
   size_t new_count;
   size_t i;
   new_count = list->count + 1;
   ObjectList_MakeRoomFor(list, new_count);

   for(i = list->count; i > index; i--)
   {
      list->list[i] = list->list[i - 1];
   }
   list->list[index] = object;

   list->count = new_count;
}

void ObjectList_InsertBefore(ObjectList_T * list, size_t index, void * object)
{
   ObjectList_InsertAt(list, index, object);
}

void ObjectList_InsertAfter(ObjectList_T * list, size_t index, void * object)
{
   ObjectList_InsertAt(list, index + 1, object);
}

void ObjectList_RemoveFast(ObjectList_T * list, size_t index)
{
   list->list[index] = list->list[list->count - 1];
   list->count --;
}

void ObjectList_RemoveOrdered(ObjectList_T * list, size_t index)
{
   size_t i;
   for(i = index + 1; i < list->count; i++)
   {
      list->list[i - 1] = list->list[i];
   }

   list->count --;
}

size_t ObjectList_Count(const ObjectList_T * list)
{
   return list->count;
}

void * ObjectList_Get(const ObjectList_T * list, size_t index)
{
   void * result;
   if(index < list->count)
   {
      result = list->list[index];
   }
   else
   {
      result = NULL;
   }
   return result;
}


void ObjectList_RemoveAll(ObjectList_T * list)
{
   list->count = 0;
}



