#ifndef __TYPEMAP_H__
#define __TYPEMAP_H__

#include "ListMemory.h"


typedef struct TypeMap_S     TypeMap_T;
typedef enum   TypeMapType_E TypeMapType_T;

enum TypeMapType_E
{
   e_TMT_NoKey,
   e_TMT_Int,
   e_TMT_Float,
   e_TMT_Pointer,
   e_TMT_String
};

struct TypeMap_S
{
   ListMemory_T pairs;
};

void TypeMap_Init(TypeMap_T * map);
void TypeMap_Destory(TypeMap_T * map);

void TypeMap_AddIntKey(TypeMap_T * map, const char * key, int value);
void TypeMap_AddFloatKey(TypeMap_T * map, const char * key, float value);
void TypeMap_AddPointerKey(TypeMap_T * map, const char * key, void * value);
void TypeMap_AddStringKey(TypeMap_T * map, const char * key, const char * value);

void TypeMap_RemoveKey(TypeMap_T * map, const char * key);
TypeMapType_T TypeMap_GetType(const TypeMap_T * map, const char * key);

int TypeMap_GetInt(const TypeMap_T * map, const char * key);
float TypeMap_GetFloat(const TypeMap_T * map, const char * key);
void * TypeMap_GetPointer(const TypeMap_T * map, const char * key);
const char * TypeMap_GetString(const TypeMap_T * map, const char * key);

void TypeMap_Clear(TypeMap_T * map);

int TypeMap_IsStringEqual(const TypeMap_T * map, const char * key, const char * cmp_value);

#endif // __TYPEMAP_H__

