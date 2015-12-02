#include "ManagerShader.h"

#include "ShaderTool.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct ShaderTable_S ShaderTable_T;
struct ShaderTable_S
{
   const char * shader_id;
   const char * vertex_filename;
   const char * geometry_filename;
   const char * fragment_filename;
};

static const ShaderTable_T SHADER_TABLE[] = 
{
   { "test1",     "test1.vert.glsl",     NULL, "test1.frag.glsl"     },
   { "block",     "block.vert.glsl",     NULL, "block.frag.glsl"     },
   { "wavefront", "wavefront.vert.glsl", NULL, "wavefront.frag.glsl" },
   { NULL,        NULL,                  NULL, NULL                  }
};


void ManagerShader_Init(ManagerShader_T * manager)
{
   ObjectList_Init(&manager->list);
   StringMap_Init(&manager->map);
}

void ManagerShader_Destroy(ManagerShader_T * manager)
{
   size_t i, count;
   GLuint ** list;

   list = ObjectList_Get(&manager->list, &count);
   for(i = 0; i < count; i++)
   {
      glDeleteProgram(*(list[i]));
   }


   ObjectList_Destory(&manager->list);
   StringMap_Destory(&manager->map);
}

static GLuint ManagerShader_Load(const char * shader_id)
{
   size_t i;
   int found;
   GLuint out;
   out = 0;
   found = 0;
   i = 0;
   while(SHADER_TABLE[i].shader_id != NULL)
   {
      if(strcmp(SHADER_TABLE[i].shader_id, shader_id) == 0)
      {
         out = ShaderTool_CreateShaderProgram(SHADER_TABLE[i].vertex_filename, 
                                              SHADER_TABLE[i].geometry_filename, 
                                              SHADER_TABLE[i].fragment_filename);
         found = 1;
         break;
      }
      i++;
   }

   if(found == 0)
   {
      printf("Error: ManagerShader_Load could not find shader id: %s\n", shader_id);
   }
   return out;
}

GLuint ManagerShader_Get(ManagerShader_T * manager, const char * shader_id)
{
   GLuint * ptr;
   ptr = StringMap_Get(&manager->map, shader_id);
   if(ptr == NULL)
   {
      ptr = malloc(sizeof(GLuint));
      ObjectList_Add(&manager->list, ptr);
      StringMap_Put(&manager->map, shader_id, ptr);
      (*ptr) = ManagerShader_Load(shader_id);
   }

   return (*ptr);
   
}

