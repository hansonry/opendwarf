#include <stdlib.h>
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLMesh.h"
#include "GLMeshBuilder.h"

#define GROW_BY 0x10

void GLMeshBuilder_Init(GLMeshBuilder_T * builder, const unsigned int * vertex_section_sizes,
                                                         unsigned int vertex_section_sizes_count)
{
   int i;
   unsigned int new_size;

   builder->vertex_section_sizes_count = vertex_section_sizes_count;
   builder->vertex_chunk_size = 0;
   for(i = 0; i < builder->vertex_section_sizes_count; i++)
   {
      builder->vertex_section_sizes[i] = vertex_section_sizes[i];
      builder->vertex_chunk_size += builder->vertex_section_sizes[i];
   }
   
   new_size = GROW_BY;
   builder->vertex_data  = malloc(new_size * builder->vertex_chunk_size * sizeof(float));
   builder->vertex_size  = new_size;
   builder->vertex_count = 0;

   builder->element_data  = malloc(new_size * sizeof(unsigned int));
   builder->element_size  = new_size;
   builder->element_count = 0;

   
}

void GLMeshBuilder_Destroy(GLMeshBuilder_T * builder)
{
   free(builder->vertex_data);
   builder->vertex_data = NULL;
   free(builder->element_data);
   builder->element_data = NULL;
}

void GLMeshBuilder_AddNVertex(GLMeshBuilder_T * builder, unsigned int n, const float * vertex_data)
{
   unsigned int i, k;
   unsigned int new_size;
   float * p;
   const float * tf;
   if(builder->vertex_count + n >= builder->vertex_size)
   {
      new_size = builder->vertex_count + n + GROW_BY;
      builder->vertex_data  = realloc(builder->vertex_data, new_size * builder->vertex_chunk_size * sizeof(float));
      builder->vertex_size  = new_size;
   }


   tf = vertex_data;
   for(k = 0; k < n; k ++)
   {

      p = &builder->vertex_data[(builder->vertex_count + k) * builder->vertex_chunk_size];

      for(i = 0; i < builder->vertex_chunk_size; i++)
      {
         p[i] = *tf;
         tf ++;
      }
   }

   builder->vertex_count += n;

}

void GLMeshBuilder_Add1Vertex(GLMeshBuilder_T * builder, const float * vertex_data)
{
   unsigned int i;
   unsigned int new_size;
   float * p;
   if(builder->vertex_count >= builder->vertex_size)
   {
      new_size = builder->vertex_size + GROW_BY;
      builder->vertex_data  = realloc(builder->vertex_data, new_size * builder->vertex_chunk_size * sizeof(float));
      builder->vertex_size  = new_size;
   }

   p = &builder->vertex_data[builder->vertex_count * builder->vertex_chunk_size];

   for(i = 0; i < builder->vertex_chunk_size; i++)
   {
      p[i] = vertex_data[i];
   }

   builder->vertex_count ++;

}

void GLMeshBuilder_Add1Vertex3f(GLMeshBuilder_T * builder, float f1, float f2, float f3)
{
   float v[3];
   v[0] = f1;
   v[1] = f2;
   v[2] = f3;
   GLMeshBuilder_Add1Vertex(builder, v);
}
void GLMeshBuilder_Add1Vertex6f(GLMeshBuilder_T * builder, float f1, float f2, float f3, float f4, float f5, float f6)
{
   float v[6];
   v[0] = f1;
   v[1] = f2;
   v[2] = f3;
   v[3] = f4;
   v[4] = f5;
   v[5] = f6;
   GLMeshBuilder_Add1Vertex(builder, v);
}

void GLMeshBuilder_Add1Vertex9f(GLMeshBuilder_T * builder, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9)
{
   float v[9];
   v[0] = f1;
   v[1] = f2;
   v[2] = f3;
   v[3] = f4;
   v[4] = f5;
   v[5] = f6;
   v[6] = f7;
   v[7] = f8;
   v[8] = f9;
   GLMeshBuilder_Add1Vertex(builder, v);
}

void GLMeshBuilder_Add1Vertex12f(GLMeshBuilder_T * builder, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12)
{
   float v[12];
   v[0] = f1;
   v[1] = f2;
   v[2] = f3;
   v[3] = f4;
   v[4] = f5;
   v[5] = f6;
   v[6] = f7;
   v[7] = f8;
   v[8] = f9;
   v[9] = f10;
   v[10] = f11;
   v[11] = f12;
   GLMeshBuilder_Add1Vertex(builder, v);
}


void GLMeshBuilder_Add1Element(GLMeshBuilder_T * builder, unsigned int e1)
{
   unsigned int e[1];
   e[0] = e1;
   GLMeshBuilder_AddElementArray(builder, e, 1);
}

void GLMeshBuilder_Add2Element(GLMeshBuilder_T * builder, unsigned int e1, unsigned int e2)
{
   unsigned int e[2];
   e[0] = e1;
   e[1] = e2;
   GLMeshBuilder_AddElementArray(builder, e, 2);
}

void GLMeshBuilder_Add3Element(GLMeshBuilder_T * builder, unsigned int e1, unsigned int e2, unsigned int e3)
{
   unsigned int e[3];
   e[0] = e1;
   e[1] = e2;
   e[2] = e3;
   GLMeshBuilder_AddElementArray(builder, e, 3);
}

void GLMeshBuilder_Add4Element(GLMeshBuilder_T * builder, unsigned int e1, unsigned int e2, unsigned int e3, unsigned int e4)
{
   unsigned int e[4];
   e[0] = e1;
   e[1] = e2;
   e[2] = e3;
   e[3] = e4;
   GLMeshBuilder_AddElementArray(builder, e, 4);
}

void GLMeshBuilder_AddElementArray(GLMeshBuilder_T * builder, const unsigned int * e, unsigned int size)
{
   unsigned int i;
   unsigned int new_size;
   unsigned int *p;
   if(builder->element_count + size >= builder->element_size)
   {
      new_size = builder->element_size + size + GROW_BY;
      builder->element_data  = realloc(builder->element_data, new_size * sizeof(unsigned int));
      builder->element_size  = new_size;
   }
   
   p = &builder->element_data[builder->element_count];
   for(i = 0; i < size; i++)
   {
      p[i] = e[i];
   }
   builder->element_count += size;
}


void GLMeshBuilder_CreateGLMesh(const GLMeshBuilder_T * builder, GLMesh_T * mesh)
{
   GLMesh_Init(mesh, builder->vertex_section_sizes,
                     builder->vertex_section_sizes_count,
                     builder->vertex_data,
                     builder->vertex_count,
                     builder->element_data,
                     builder->element_count);
}







