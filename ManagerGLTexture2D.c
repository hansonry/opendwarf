#include "ManagerGLTexture2D.h"


#include <stdlib.h>


void ManagerGLTexture2D_Init(ManagerGLTexture2D_T * manager)
{
   ObjectList_Init(&manager->list);
   StringMap_Init(&manager->map);

}

void ManagerGLTexture2D_Destory(ManagerGLTexture2D_T * manager)
{
   size_t i , count;
   GLTexture2D_T ** list;

   list = ObjectList_Get(&manager->list, &count);

   for(i = 0; i < count; i++)
   {
      GLTexture2D_Destroy(list[i]);
      free(list[i]);
   }

   
   
   ObjectList_Destory(&manager->list);
   StringMap_Destory(&manager->map);
}

GLTexture2D_T * ManagerGLTexture2D_Get(ManagerGLTexture2D_T * manager, const char * filename)
{
   GLTexture2D_T * out;
   out = StringMap_Get(&manager->map, filename);
   if(out == NULL)
   {
      out = malloc(sizeof(GLTexture2D_T));
      GLTexture2D_Load(out, filename);
      ObjectList_Add(&manager->list, out);
      StringMap_Put(&manager->map, filename, out);
   }
   return out;
}


