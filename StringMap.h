#ifndef __STRINGMAP_H__
#define __STRINGMAP_H__
#include <stddef.h>

typedef struct StringMap_S StringMap_T;
typedef struct StringMapElement_S StringMapElement_T;

struct StringMap_S
{
   StringMapElement_T * list;
   size_t               list_count;
   size_t               list_size;
};

void StringMap_Init(StringMap_T * map);
void StringMap_Destory(StringMap_T * map);

void   StringMap_Put(StringMap_T * map, const char * key, void * value);
void * StringMap_Get(const StringMap_T * map, const char * key);
int    StringMap_HasKey(const StringMap_T * map, const char * key);

#endif // __STRINGMAP_H__

