#ifndef __GLMESHNODE_H__
#define __GLMESHNODE_H__
#include "GLMesh.h"
#include "SceneGraph.h"
#include "Shader.h"

typedef struct GLMeshNode_S GLMeshNode_T;

struct GLMeshNode_S
{
   SGNode_T * node;
   GLMesh_T * mesh;
   GLenum     mesh_mode;
   Shader_T * shader;
};

void GLMeshNode_Init(GLMeshNode_T * node, SceneGraph_T * graph,
                                          GLMesh_T * mesh, 
                                          GLenum mesh_mode);
void GLMeshNode_Destroy(GLMeshNode_T * node);

SGNode_T * GLMeshNode_GetNode(GLMeshNode_T * node);




#endif // __GLMESHNODE_H__

