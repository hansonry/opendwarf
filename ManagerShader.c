#include "ManagerShader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void ManagerShader_Init(ManagerShader_T * manager)
{
   ObjectList_Init(&manager->list);
   StringMap_Init(&manager->map);
}

void ManagerShader_Destroy(ManagerShader_T * manager)
{
   size_t i, count;
   Shader_T ** list;

   list = ObjectList_Get(&manager->list, &count);
   for(i = 0; i < count; i++)
   {
      Shader_Free(list[i]);
   }


   ObjectList_Destory(&manager->list);
   StringMap_Destory(&manager->map);
}


Shader_T * ManagerShader_Get(ManagerShader_T * manager, const char * shader_id)
{
   Shader_T * ptr;
   ptr = StringMap_Get(&manager->map, shader_id);
   if(ptr == NULL)
   {
      ptr = Shader_Create(shader_id);
      ObjectList_Add(&manager->list, ptr);
      StringMap_Put(&manager->map, shader_id, ptr);
   }

   return ptr;
   
}


