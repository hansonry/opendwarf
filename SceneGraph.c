#include <stdlib.h>
#include "SceneGraph.h"

void SceneGraph_Init(SceneGraph_T * graph)
{
   graph->root = NULL;
}

void SceneGraph_Destroy(SceneGraph_T * graph)
{

}


static void SceneGraph_RenderLoop(SGNode_T * loop, GFXState_T * state, const Matrix3D_T * parent_matrix, int parent_flag_recompute)
{
   size_t i, count;
   SGNode_T ** node_list;
   int local_flag_recompute;
   //printf("Here\n");
   if(loop != NULL)
   {
      if(loop->trans.flag_recompute == 1 || parent_flag_recompute == 1)
      {
         local_flag_recompute = 1;
      }
      else
      {
         local_flag_recompute = 0;
      }

      if(local_flag_recompute == 1)
      {
         loop->trans.flag_recompute = 0;
         Matrix3D_Multiply(&loop->trans.final, parent_matrix, &loop->trans.delta);
         //printf("Here\n");
      }

      if(loop->type == e_SGNT_Branch)
      {
         node_list = ListMemory_Get(&loop->data.branch.children, &count, NULL);
         for(i = 0; i < count; i++)
         {
            SceneGraph_RenderLoop(node_list[i], state, &loop->trans.final, local_flag_recompute);
         }
      }
      else if(loop->type == e_SGNT_Leaf)
      {
         if(loop->data.leaf.callback != NULL)
         {
            GFXState_SetWorldMatrix(state, &loop->trans.final);
            loop->data.leaf.callback(loop, state);
         }
      }
   }
}

void SceneGraph_Render(SceneGraph_T * graph, GFXState_T * state)
{
   Matrix3D_T matrix;
   //printf("Render\n");
   Matrix3D_SetIdentity(&matrix);
   SceneGraph_RenderLoop(graph->root, state, &matrix, 0);
}

void SceneGraph_SetRootNode(SceneGraph_T * graph, SGNode_T * node)
{
   graph->root = node;
}

static SGNode_T * SceneGraph_Node_New(SceneGraph_T * graph, const Matrix3D_T * diff)
{
   SGNode_T * node;
   node = malloc(sizeof(SGNode_T));
   Matrix3D_SetIdentity(&node->trans.final);
   if(diff == NULL)
   {
      Matrix3D_SetIdentity(&node->trans.delta);
   }
   else
   {
      Matrix3D_Copy(&node->trans.delta, diff);
   }
   node->trans.flag_recompute = 1;
   return node;
}

SGNode_T * SceneGraph_Node_NewBranch(SceneGraph_T * graph, const Matrix3D_T * diff)
{
   SGNode_T * node;
   node = SceneGraph_Node_New(graph, diff);
   node->type = e_SGNT_Branch;
   ListMemory_Init(&node->data.branch.children, sizeof(SGNode_T *), 0);
   return node;
}

SGNode_T * SceneGraph_Node_NewLeaf(SceneGraph_T * graph, const Matrix3D_T * diff, SGNodeCallback_T callback, void * object)
{
   SGNode_T * node;
   node = SceneGraph_Node_New(graph, diff);
   node->type = e_SGNT_Leaf;
   node->data.leaf.callback = callback;
   node->data.leaf.object = object;
   return node;
}

static int SceneGraph_Branch_GetChildIndex(SGN_Branch_T * branch, SGNode_T * child)
{
      int result_index;
      size_t i, count;
      SGNode_T ** child_list;

      result_index = -1;
      child_list = ListMemory_Get(&branch->children, &count, NULL);

      for(i = 0; i < count; i++)
      {
         if(child_list[i] == child)
         {
            result_index = (int)i;
            break;
         }
      }

      return result_index;
}

int SceneGraph_Node_ChildAdd(SGNode_T * node, SGNode_T * child)
{
   int result;
   int index;
   SGN_Branch_T * branch;
   if(node->type == e_SGNT_Branch && child != NULL)
   {
      branch = &node->data.branch;
      index = SceneGraph_Branch_GetChildIndex(branch, child);
      if(index < 0)
      {
         ListMemory_CopyAlloc(&branch->children, &child, NULL);
         result = 1;
      }
      else
      {
         result = 0;
      }
   }
   else
   {
      result = 0;
   }
   return result;
}

int SceneGraph_Node_ChildRemove(SGNode_T * node, SGNode_T * child)
{
   int result;
   int index;
   SGN_Branch_T * branch;
   if(node->type == e_SGNT_Branch && child != NULL)
   {
      branch = &node->data.branch;
      index = SceneGraph_Branch_GetChildIndex(branch, child);
      if(index >= 0)
      {
         ListMemory_FreeNow(&branch->children, index);
         result = 1;
      }
      else
      {
         result = 0;
      }
   }
   else
   {
      result = 0;
   }
   return result;
}

void SceneGraph_Node_SetMatrix(SGNode_T * node, const Matrix3D_T * diff)
{
   Matrix3D_Copy(&node->trans.delta, diff);
   node->trans.flag_recompute = 1;
}
