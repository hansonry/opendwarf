#ifndef __GLMESHNODE_H__
#define __GLMESHNODE_H__
#include "GLMesh.h"
#include "SceneGraph.h"
#include "ColorTextureLightShader.h"

typedef struct GLMeshNode_S GLMeshNode_T;
typedef struct GLMeshNodeData_S GLMeshNodeData_T;
struct GLMeshNodeData_S
{
   GLMesh_T                  * mesh;
   GLenum                      mesh_mode;
   ColorTextureLightShader_T * shader;
};

struct GLMeshNode_S
{
   SGNode_T         * node;
   GLMeshNodeData_T * data;
};

void GLMeshNode_Init(GLMeshNode_T * node, SceneGraph_T * graph,
                                          GLMesh_T * mesh, 
                                          GLenum mesh_mode);
void GLMeshNode_Destroy(GLMeshNode_T * node);

SGNode_T * GLMeshNode_GetNode(GLMeshNode_T * node);




#endif // __GLMESHNODE_H__

