#include "TypeMap.h"

#include <string.h>

typedef struct TypeMapPair_S TypeMapPair_T;

struct TypeMapPair_S
{
   TypeMapType_T type;
   const char * key;
   union
   {
      int          v_int;
      float        v_float;
      void       * v_pointer;
      const char * v_string;
   } value;
};


static const TypeMapPair_T * TypeMap_FindPair(const TypeMap_T * map, const char * key)
{
   const TypeMapPair_T * result, * list;
   size_t i, count;
   result = NULL;
   list = ArrayList_Get((ArrayList_T*)&map->pairs, &count, NULL);
   for(i = 0; i < count; i ++)
   {
      if(strcmp(list[i].key, key) == 0)
      {
         result = &list[i];
         break;
      }
   }

   return result;
}

static TypeMapPair_T * TypeMap_GetMemory(TypeMap_T * map, const char * key)
{
   TypeMapPair_T * pair;
   pair = (TypeMapPair_T *)TypeMap_FindPair(map, key);
   if(pair == NULL)
   {
      pair = ArrayList_Allocate(&map->pairs, NULL);
   }
   pair->key = key;
   return pair;
}

void TypeMap_Init(TypeMap_T * map)
{
   ArrayList_Init(&map->pairs, sizeof(TypeMapPair_T), 0);
}

void TypeMap_Destory(TypeMap_T * map)
{
   ArrayList_Destory(&map->pairs);
}

void TypeMap_AddIntKey(TypeMap_T * map, const char * key, int value)
{
   TypeMapPair_T * pair;
   pair = TypeMap_GetMemory(map, key);
   
   pair->type = e_TMT_Int;
   pair->value.v_int = value;
}

void TypeMap_AddFloatKey(TypeMap_T * map, const char * key, float value)
{
   TypeMapPair_T * pair;

   pair = TypeMap_GetMemory(map, key);
   
   pair->type = e_TMT_Float;
   pair->value.v_float = value;
}

void TypeMap_AddPointerKey(TypeMap_T * map, const char * key, void * value)
{
   TypeMapPair_T * pair;

   pair = TypeMap_GetMemory(map, key);
   
   pair->type = e_TMT_Pointer;
   pair->value.v_pointer = value;
}

void TypeMap_AddStringKey(TypeMap_T * map, const char * key, const char * value)
{
   TypeMapPair_T * pair;

   pair = TypeMap_GetMemory(map, key);
   
   pair->type = e_TMT_String;
   pair->value.v_string = value;
}

void TypeMap_RemoveKey(TypeMap_T * map, const char * key)
{
   TypeMapPair_T * pair, * list;
   size_t i, count;

   list = ArrayList_Get(&map->pairs, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(strcmp(list[i].key, key) == 0)
      {
         ArrayList_FreeNow(&map->pairs, i);
         break;
      }
   }

}

TypeMapType_T TypeMap_GetType(const TypeMap_T * map, const char * key)
{
   TypeMapType_T result;
   const TypeMapPair_T * pair;

   pair = TypeMap_FindPair(map, key);

   if(pair == NULL)
   {
      result = e_TMT_NoKey;
   }
   else
   {
      result = pair->type;
   }
   return result;
}

int TypeMap_GetInt(const TypeMap_T * map, const char * key)
{
   const TypeMapPair_T * pair;
   int result;

   pair = TypeMap_FindPair(map, key);
   
   if(pair == NULL || pair->type != e_TMT_Int)
   {
      result = 0;
   }
   else
   {
      result = pair->value.v_int; 
   }
   return result;
}

float TypeMap_GetFloat(const TypeMap_T * map, const char * key)
{
   const TypeMapPair_T * pair;
   float result;

   pair = TypeMap_FindPair(map, key);
   
   if(pair == NULL || pair->type != e_TMT_Float)
   {
      result = 0;
   }
   else
   {
      result = pair->value.v_float; 
   }
   return result;
}

void * TypeMap_GetPointer(const TypeMap_T * map, const char * key)
{
   const TypeMapPair_T * pair;
   void * result;

   pair = TypeMap_FindPair(map, key);
   
   if(pair == NULL || pair->type != e_TMT_Pointer)
   {
      result = NULL;
   }
   else
   {
      result = pair->value.v_pointer; 
   }
   return result;
}

const char * TypeMap_GetString(const TypeMap_T * map, const char * key)
{
   const TypeMapPair_T * pair;
   const char * result;

   pair = TypeMap_FindPair(map, key);
   
   if(pair == NULL || pair->type != e_TMT_String)
   {
      result = NULL;
   }
   else
   {
      result = pair->value.v_string; 
   }
   return result;
}


void TypeMap_Clear(TypeMap_T * map)
{
   ArrayList_Clear(&map->pairs);
}

int TypeMap_IsStringEqual(const TypeMap_T * map, const char * key, const char * cmp_value)
{
   const TypeMapPair_T * pair;
   int result;

   pair = TypeMap_FindPair(map, key);
   
   if(pair == NULL || pair->type != e_TMT_String)
   {
      result = 0;
   }
   else
   {
      if(strcmp(pair->value.v_string, cmp_value) == 0)
      {
         result = 1;
      }
      else
      {
         result = 0;
      }
   }
   return result;
}



