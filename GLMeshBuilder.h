#ifndef __GLMESHBUILDER_H__
#define __GLMESHBUILDER_H__

typedef struct GLMeshBuilder_S GLMeshBuilder_T;
struct GLMeshBuilder_S
{
   float        * vertex_data;
   unsigned int   vertex_size;
   unsigned int   vertex_count;
   unsigned int   vertex_chunk_size;
   unsigned int * element_data;
   unsigned int   element_count;
   unsigned int   element_size;
   unsigned int   vertex_section_sizes[8];
   unsigned int   vertex_section_sizes_count;
};


void GLMeshBuilder_Init(GLMeshBuilder_T * builder, const unsigned int * vertex_section_sizes,
                                                         unsigned int vertex_section_sizes_count);
void GLMeshBuilder_Destroy(GLMeshBuilder_T * builder);

void GLMeshBuilder_Add1Vertex(GLMeshBuilder_T * builder, const float * vertex_data);
void GLMeshBuilder_Add1Vertex3f(GLMeshBuilder_T * builder, float f1, float f2, float f3);
void GLMeshBuilder_Add1Vertex6f(GLMeshBuilder_T * builder, float f1, float f2, float f3, float f4, float f5, float f6);
void GLMeshBuilder_Add1Vertex9f(GLMeshBuilder_T * builder, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9);
void GLMeshBuilder_Add1Vertex12f(GLMeshBuilder_T * builder, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12);

void GLMeshBuilder_Add1Element(GLMeshBuilder_T * builder, unsigned int e1);
void GLMeshBuilder_Add2Element(GLMeshBuilder_T * builder, unsigned int e1, unsigned int e2);
void GLMeshBuilder_Add3Element(GLMeshBuilder_T * builder, unsigned int e1, unsigned int e2, unsigned int e3);
void GLMeshBuilder_Add4Element(GLMeshBuilder_T * builder, unsigned int e1, unsigned int e2, unsigned int e3, unsigned int e4);
void GLMeshBuilder_AddElementArray(GLMeshBuilder_T * builder, const unsigned int * e, unsigned int size);

void GLMeshBuilder_CreateGLMesh(const GLMeshBuilder_T * builder, GLMesh_T * mesh);


#endif // __GLMESHBUILDER_H__

