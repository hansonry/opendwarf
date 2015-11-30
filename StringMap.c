#include "StringMap.h"

#include <stdlib.h>
#include <string.h>

#define GROW_BY 16

struct StringMapElement_S
{
   void * ptr;
   char * str;
};

void StringMap_Init(StringMap_T * map)
{
   map->list       = NULL;
   map->list_size  = 0;
   map->list_count = 0;
}

void StringMap_Destory(StringMap_T * map)
{
   if(map->list != NULL)
   {
      free(map->list);
      map->list = NULL;
   }
   map->list_size  = 0;
   map->list_count = 0;
}

static char * StringMap_CopyString(const char * str)
{
   char * out;
   size_t size;
   size = strlen(str) + 1;
   out = malloc(sizeof(char) * size);
   memcpy(out, str, sizeof(char) * size);
   return out;
}

static StringMapElement_T * StringMap_CreateElement(StringMap_T * map, const char * key)
{
   StringMapElement_T * ele;
   size_t new_size;
   if(map->list == NULL)
   {
      new_size = GROW_BY;
      map->list = malloc(sizeof(void*) * new_size);
      map->list_count = 0;
      map->list_size = new_size;
   }
   else if(map->list_count >= map->list_size)
   {
      new_size = map->list_size + GROW_BY;
      map->list = realloc(map->list, sizeof(void*) * new_size);
      map->list_size = new_size;
      
   }

   ele = &map->list[map->list_count];
   map->list_count ++;



   ele->str = StringMap_CopyString(key);
   return ele;
}

void StringMap_Put(StringMap_T * map, const char * key, void * value)
{
   StringMapElement_T * ele;
   ele = StringMap_CreateElement(map, key);
   ele->ptr = value;

}

static StringMapElement_T * StringMap_Lookup(const StringMap_T * map, const char * key)
{
   StringMapElement_T * ele;
   size_t i;
   ele = NULL;

   for(i = 0; i < map->list_size; i++)
   {
      if(strcmp(key, map->list[i].str) == 0)
      {
         ele = &map->list[i];
         break;
      }
   }
   return ele;

}

void * StringMap_Get(const StringMap_T * map, const char * key)
{
   StringMapElement_T * ele;
   ele = StringMap_Lookup(map, key);
   if(ele == NULL)
   {
      return NULL;
   }
   else
   {
      return ele->ptr;
   }
}

int StringMap_HasKey(const StringMap_T * map, const char * key)
{
   StringMapElement_T * ele;
   ele = StringMap_Lookup(map, key);
   if(ele == NULL)
   {
      return 0;
   }
   else
   {
      return 1;
   }
}

