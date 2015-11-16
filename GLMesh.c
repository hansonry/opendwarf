#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLMesh.h"


void GLMesh_Init(GLMesh_T * mesh, const unsigned int * vertex_section_sizes,
                                  unsigned int vertex_section_sizes_count,
                                  const float * vertex_data, 
                                  unsigned int vertex_count,
                                  const unsigned int * element_data,
                                  unsigned int element_count)
{
   int i;

   mesh->vertex_section_sizes_count = vertex_section_sizes_count;
   mesh->vertex_data                = vertex_data;
   mesh->vertex_count               = vertex_count;
   mesh->element_data               = element_data;
   mesh->element_count              = element_count;
   mesh->on_gfx_card_flag           = 0;
   mesh->vbo                        = 0;
   mesh->ibo                        = 0;

   // compute vertex size
   mesh->vertex_size = 0;
   for(i = 0; i < mesh->vertex_section_sizes_count; i++)
   {
      mesh->vertex_section_sizes[i] = vertex_section_sizes[i];
      mesh->vertex_size += mesh->vertex_section_sizes[i];
      //printf("s = %i\n", mesh->vertex_size);
   }
}

void GLMesh_Cleanup(GLMesh_T * mesh)
{
   GLMesh_RemoveFromGFXCard(mesh);
}

void GLMesh_MoveToGFXCard(GLMesh_T * mesh)
{
   if(mesh->on_gfx_card_flag == 0)
   {

      glGenBuffers(1, &mesh->vbo);
      glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->vertex_size * mesh->vertex_count, mesh->vertex_data, GL_STATIC_DRAW);

      glGenBuffers(1, &mesh->ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->element_count, mesh->element_data, GL_STATIC_DRAW);

      mesh->on_gfx_card_flag = 1;
   }
}

void GLMesh_RemoveFromGFXCard(GLMesh_T * mesh)
{
   if(mesh->on_gfx_card_flag == 1)
   {
      glDeleteBuffers(1, &mesh->vbo);
      glDeleteBuffers(1, &mesh->ibo);
      mesh->vbo = 0;
      mesh->ibo = 0;
      mesh->on_gfx_card_flag = 0;
   }
}

void GLMesh_Render(GLMesh_T * mesh, GLenum mode)
{
   int i;
   unsigned int l_size;
   unsigned int offset_so_far;
   if(mesh->on_gfx_card_flag == 1)
   {
      glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
      
      offset_so_far = 0;
      for(i = 0; i < mesh->vertex_section_sizes_count; i++)
      {
         l_size = mesh->vertex_section_sizes[i];
         //printf("%i == 3\n", l_size);
         if(l_size > 0)
         {
            glVertexAttribPointer(i, l_size, GL_FLOAT, GL_FALSE, (mesh->vertex_size - l_size) * sizeof(float), (GLvoid *)offset_so_far);
            //printf("glVAP(%i, %i, GL_FLOAT, GL_FALSE, %i, %i)\n", i, l_size, (mesh->vertex_size - l_size) * sizeof(float), offset_so_far);
            offset_so_far += sizeof(float) * l_size;
         }
      }
      
      //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glDrawElements(mode, mesh->element_count, GL_UNSIGNED_INT, 0);
   }
   else
   {
      // TODO: Support me?
   }
}

