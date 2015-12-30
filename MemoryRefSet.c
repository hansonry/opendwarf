#include "MemoryRefSet.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MemoryRefSetEntry_S MemoryRefSetEntry_T;

struct MemoryRefSetEntry_S
{
   size_t array_size;
   int    ref_count;
   void * ptr;
};


void MemoryRefSet_Init(MemoryRefSet_T * mem, size_t element_size, MemoryRefSet_Freeer_T freer)
{
   mem->element_size = element_size;
   mem->freer        = freer;
   ListMemory_Init(&mem->memory_list, sizeof(MemoryRefSetEntry_T), 0);
}

void MemoryRefSet_Destroy(MemoryRefSet_T * mem)
{
   MemoryRefSetEntry_T * e_list;
   size_t i, count;

   e_list = ListMemory_Get(&mem->memory_list, &count, NULL);

   for(i = 0; i < count; i++)
   {
      if(mem->freer != NULL)
      {
         mem->freer(e_list[i].ptr);
      }
      free(e_list[i].ptr);
   }

   ListMemory_Destory(&mem->memory_list);
}


void * MemoryRefSet_Allocate(MemoryRefSet_T * mem)
{
   MemoryRefSetEntry_T entry;
   entry.ptr        = malloc(mem->element_size);
   entry.ref_count  = 0;
   entry.array_size = 1;
   ListMemory_CopyAlloc(&mem->memory_list, &entry, NULL);
   return entry.ptr;
}

void * MemoryRefSet_CopyAllocate(MemoryRefSet_T * mem, const void * data)
{
   void * l_mem;
   l_mem = MemoryRefSet_Allocate(mem);
   memcpy(l_mem, data, mem->element_size);
   return l_mem;
}

void * MemoryRefSet_ArrayAllocate(MemoryRefSet_T * mem, size_t count)
{
   MemoryRefSetEntry_T entry;
   entry.ptr        = malloc(mem->element_size * count);
   entry.ref_count  = 0;
   entry.array_size = count;
   ListMemory_CopyAlloc(&mem->memory_list, &entry, NULL);
   return entry.ptr;
}

static MemoryRefSetEntry_T * MemoryRefSet_FindMem(MemoryRefSet_T * mem, void * object)
{
   MemoryRefSetEntry_T * entry;
   MemoryRefSetEntry_T * e_list;
   size_t count, i;
   entry = NULL;

   e_list = ListMemory_Get(&mem->memory_list, &count, NULL);

   for(i = 0; i < count; i++)
   {
      if(e_list[i].ptr == object)
      {
         entry = &e_list[i];
         break;
      }
   }

   return entry;
}

void MemoryRefSet_Keep(MemoryRefSet_T * mem, void * object)
{
   MemoryRefSetEntry_T * entry;
   entry = MemoryRefSet_FindMem(mem, object);
   if(entry == NULL)
   {
      printf("Error: MemoryRefSet_Keep: Couldn't find entry for object %p in MemoryRefSet %p\n", object, mem);
   }
   else
   {
      entry->ref_count ++;
   }

}

void MemoryRefSet_Release(MemoryRefSet_T * mem, void * object)
{
   MemoryRefSetEntry_T * entry;
   entry = MemoryRefSet_FindMem(mem, object);
   if(entry == NULL)
   {
      printf("Error: MemoryRefSet_Release: Couldn't find entry for object %p in MemoryRefSet %p\n", object, mem);
   }
   else
   {
      entry->ref_count --;
   }
}

void MemoryRefSet_CheckCounts(MemoryRefSet_T * mem)
{
   MemoryRefSetEntry_T * e_list;
   size_t count, i;

   e_list = ListMemory_Get(&mem->memory_list, &count, NULL);

   for(i = 0; i < count; i++)
   {
      if(e_list[i].ref_count <= 0)
      {
         if(mem->freer != NULL)
         {
            mem->freer(e_list[i].ptr);
         }
         free(e_list[i].ptr);
         e_list[i].ptr = NULL;
         ListMemory_FreeLater(&mem->memory_list, i);
      }
   }

   ListMemory_FlushFree(&mem->memory_list);

}

