#include "GLMeshNode.h"
#include "RenderResources.h"


static void GLMeshNode_DrawCallback(SGNode_T * node, GFXState_T * state)
{
   GLMeshNode_T * mesh_node;
   mesh_node = node->data.leaf.object;

   GFXState_SetShaderAndUpdateUniforms(state, mesh_node->shader);

   GLMesh_Render(mesh_node->mesh, mesh_node->mesh_mode);

}

void GLMeshNode_Init(GLMeshNode_T * node, SceneGraph_T * graph,
                                          GLMesh_T * mesh, 
                                          GLenum mesh_mode)
{
   ManagerShader_T * manager_shader;

   manager_shader = Resources_GetShaderManager();
   node->shader = ManagerShader_Get(manager_shader, "color_texture_light");

   node->mesh = mesh;
   node->mesh_mode = mesh_mode;
   node->node = SceneGraph_Node_NewLeaf(graph, NULL, GLMeshNode_DrawCallback, node);   
}

void GLMeshNode_Destroy(GLMeshNode_T * node)
{
}

SGNode_T * GLMeshNode_GetNode(GLMeshNode_T * node)
{
   return node->node;
}

