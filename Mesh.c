#include <stdlib.h>
#include "SDL2/SDL_opengl.h"
#include "Mesh.h"

#define GROW_BY 0x10

#define MESH_STATE_INGFXCARD 0x01

#define HAS_FLAG(a, f)  (((a) & (f)) == (f))


void Mesh_Setup(Mesh_T * mesh, int flags, GLenum mode)
{
   unsigned int new_size;
   mesh->flags             = flags;
   mesh->gl_mode           = mode;
   mesh->state_flags       = 0x00;
   mesh->gl_vertex_buffer  = 0;
   mesh->gl_element_buffer = 0;

   mesh->vertex_chunk_size = 0;
   if(HAS_FLAG(mesh->flags, MESH_VERTEX))
   {
      mesh->vertex_chunk_size += 3;
   }
   if(HAS_FLAG(mesh->flags, MESH_NORMAL))
   {
      mesh->vertex_chunk_size += 3;
   }
   if(HAS_FLAG(mesh->flags, MESH_COLOR))
   {
      mesh->vertex_chunk_size += 4;
   }
   if(HAS_FLAG(mesh->flags, MESH_UV))
   {
      mesh->vertex_chunk_size += 2;
   }

   new_size = GROW_BY;

   mesh->vertex_data       = calloc(new_size, mesh->vertex_chunk_size * sizeof(float));
   mesh->vertex_size       = new_size;
   mesh->vertex_count      = 0;
   mesh->element_data      = calloc(new_size, sizeof(unsigned int));
   mesh->element_size      = new_size;
   mesh->element_count     = 0;
}

void Mesh_Cleanup(Mesh_T * mesh)
{
}

void Mesh_Set3f(Mesh_T * mesh, int flag, float x, float y, float z)
{
}

void Mesh_Add3f(Mesh_T * mesh, int flag, float x, float y, float z)
{
}

void Mesh_Set2f(Mesh_T * mesh, int flag, float x, float y)
{
}

void Mesh_Add2f(Mesh_T * mesh, int flag, float x, float y)
{
}

void Mesh_Add1ui(Mesh_T * mesh, unsigned int ui1)
{
}

void Mesh_Add2ui(Mesh_T * mesh, unsigned int ui1, unsigned int ui2)
{
}

void Mesh_Add3ui(Mesh_T * mesh, unsigned int ui1, unsigned int ui2, unsigned int ui3)
{
}

void Mesh_MoveToGFXCard(Mesh_T * mesh)
{
}

void Mesh_ClearLocalMemory(Mesh_T * mesh)
{
}

void Mesh_RemoveFromGFXCard(Mesh_T * mesh)
{
}

void Mesh_RenderSetupGL(Mesh_T * mesh)
{
}

