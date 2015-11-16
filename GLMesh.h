#ifndef __GLMESH_H__
#define __GLMESH_H__


typedef struct GLMesh_S GLMesh_T;
struct GLMesh_S
{
         GLuint         vbo;
         GLuint         ibo;
         int            on_gfx_card_flag;
   const unsigned int * element_data;
         unsigned int   element_count;
   const float        * vertex_data;
         unsigned int   vertex_count;
         unsigned int   vertex_section_sizes[8];
         unsigned int   vertex_section_sizes_count;
         unsigned int   vertex_size;
};

void GLMesh_Init(GLMesh_T * mesh, const unsigned int *vertex_section_sizes,
                                  unsigned int vertex_section_sizes_count,
                                  const float * vertex_data, 
                                  unsigned int vertex_count,
                                  const unsigned int * element_data,
                                  unsigned int element_count);
void GLMesh_Cleanup(GLMesh_T * mesh);

void GLMesh_MoveToGFXCard(GLMesh_T * mesh);
void GLMesh_RemoveFromGFXCard(GLMesh_T * mesh);

void GLMesh_Render(GLMesh_T * mesh, GLenum mode);



#endif // __GLMESH_H__

