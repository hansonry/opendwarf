#ifndef __MESH_H__
#define __MESH_H__

#define MESH_VERTEX 0x01
#define MESH_COLOR  0x02
#define MESH_NORMAL 0x04
#define MESH_UV     0x08


typedef struct Mesh_S Mesh_T;
struct Mesh_S
{
   int            flags;
   int            state_flags;
   float        * vertex_data;
   unsigned int * element_data;
   unsigned int   element_count;
   unsigned int   element_size;
   unsigned int   vertex_count;
   unsigned int   vertex_size;
   unsigned int   vertex_chunk_size;
   GLuint         gl_vertex_buffer;
   GLuint         gl_element_buffer;
   GLenum         gl_mode;
};


void Mesh_Setup(Mesh_T * mesh, int flags, GLenum mode);
void Mesh_Cleanup(Mesh_T * mesh);

void Mesh_Set3f(Mesh_T * mesh, int flag, float x, float y, float z);
void Mesh_Add3f(Mesh_T * mesh, int flag, float x, float y, float z);

void Mesh_Set2f(Mesh_T * mesh, int flag, float x, float y);
void Mesh_Add2f(Mesh_T * mesh, int flag, float x, float y);

void Mesh_Add1ui(Mesh_T * mesh, unsigned int ui1);
void Mesh_Add2ui(Mesh_T * mesh, unsigned int ui1, unsigned int ui2);
void Mesh_Add3ui(Mesh_T * mesh, unsigned int ui1, unsigned int ui2, unsigned int ui3);

void Mesh_MoveToGFXCard(Mesh_T * mesh);
void Mesh_ClearLocalMemory(Mesh_T * mesh);
void Mesh_RemoveFromGFXCard(Mesh_T * mesh);

void Mesh_RenderSetupGL(Mesh_T * mesh);



#endif // __MESH_H__

