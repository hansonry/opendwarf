#include "ObjectList.h"

#include <stdlib.h>


#define GROW_BY 16
void ObjectList_Init(ObjectList_T * list)
{
   list->list = NULL;
   list->count = 0;
   list->size = 0;
}

void ObjectList_Destory(ObjectList_T * list)
{
   if(list->list != NULL)
   {
      free(list->list);
      list->list = NULL;
   }
   list->count = 0;
   list->size  = 0;
}

void ObjectList_Add(ObjectList_T * list, void * obj)
{
   size_t new_size;
   if(list->list == NULL)
   {
      list->count = 0;
      new_size = GROW_BY;
      list->list = malloc(sizeof(void *) * new_size);
      list->size = new_size;
   }
   else if(list->count >= list->size)
   {
      new_size = list->count + GROW_BY;
      list->list = realloc(list->list, sizeof(void *) * new_size);
      list->size = new_size;
   }

   list->list[list->count] = obj;
   list->count ++;
}


void ObjectList_Remove(ObjectList_T * list, void * obj)
{
   size_t index;
   int found;

   found = 0;

   for(index = 0; index < list->count; index ++)
   {
      if(list->list[index] == obj)
      {
         found = 1;
         break;
      }
   }

   if(found == 1)
   {
      list->count --;
      list->list[index] = list->list[list->count];
   }
}

void * ObjectList_Get(ObjectList_T * list, size_t * count)
{
   if(count != NULL)
   {
      (*count) = list->count;
   }
   return list->list;
}

void ObjectList_RemoveAll(ObjectList_T * list)
{
   list->count = 0;
}

