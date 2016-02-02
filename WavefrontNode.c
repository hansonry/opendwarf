#include "WavefrontNode.h"
#include "RenderResources.h"

#include <stdlib.h>


static void WavefrontNode_DrawCallback(SGNode_T * node, GFXState_T * state)
{
   WavefrontNodeData_T * w_node;
   w_node = node->data.leaf.object;
   GFXState_SetShader(state, &w_node->shader->parent);

   WavefrontShader_SetState(w_node->shader, state);
   WavefrontMesh_Render(w_node->mesh, w_node->shader->uniform_texture);
}

void WavefrontNode_Init(WavefrontNode_T * node, SceneGraph_T * graph,
                                                WavefrontMesh_T * mesh)
{
   ManagerShader_T * manager_shader;
   node->data = malloc(sizeof(WavefrontNodeData_T));

   manager_shader = Resources_GetShaderManager();
   node->data->shader = (WavefrontShader_T*)ManagerShader_Get(manager_shader, "wavefront");

   node->data->mesh = mesh;
   node->node = SceneGraph_Node_NewLeaf(graph, NULL, WavefrontNode_DrawCallback, node->data);   
}

void WavefrontNode_Destroy(WavefrontNode_T * node)
{
   free(node->data);
}

SGNode_T * WavefrontNode_GetNode(WavefrontNode_T * node)
{
   return node->node;
}
