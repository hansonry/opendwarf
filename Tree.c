#include <stdlib.h>
#include "Tree.h"


typedef unsigned char byte_t;

void Tree_Init(Tree_T * tree)
{
   tree->root = NULL;
   ObjectList_Init(&tree->node_list);

}

void Tree_Destroy(Tree_T * tree)
{
   size_t i, count;
   TreeNode_T ** node_list;
   tree->root = NULL;

   node_list = ObjectList_Get(&tree->node_list, &count);

   for(i = 0; i < count; i ++)
   {
      if(node_list[i]->owns_object == 1 && node_list[i]->callback != NULL)
      {
         node_list[i]->callback(node_list[i], e_TNE_Destory, NULL);
      }
      free(node_list[i]);
   }

   ObjectList_Destory(&tree->node_list);

}

TreeNode_T * Tree_NewNodeWithNewObject(Tree_T * tree, TreeNodeCallback_T callback, size_t object_size)
{
   TreeNode_T * node;
   node = malloc(sizeof(TreeNode_T) + object_size);

   ListMemory_Init(&node->childeren, sizeof(TreeNode_T *), 0);
   node->callback = callback;
   node->owns_object = 1;
   node->object = ((byte_t*)node) + sizeof(TreeNode_T);
   ObjectList_Add(&tree->node_list, node);

   if(node->callback != NULL)
   {
      node->callback(node, e_TNE_New, NULL);
   }
   return node;
}

TreeNode_T * Tree_NewNode(Tree_T * tree, TreeNodeCallback_T callback, void * object)
{
   TreeNode_T * node;
   node = malloc(sizeof(TreeNode_T));

   ListMemory_Init(&node->childeren, sizeof(TreeNode_T *), 0);
   node->callback = callback;
   node->owns_object = 0;
   node->object = object;
   ObjectList_Add(&tree->node_list, node);
   return node;
}


void Tree_SetRootNode(Tree_T * tree, TreeNode_T * node)
{
   tree->root = node;
}

void Tree_RunLoop(TreeNode_T * node, TreeNode_T * parent)
{
   size_t i, count;
   TreeNode_T ** node_list;

   if(node != NULL)
   {
      if(node->callback != NULL)
      {
         node->callback(node, e_TNE_Enter, parent);
      }

      node_list = ListMemory_Get(&node->childeren, &count, NULL);
      for(i = 0; i < count; i ++)
      {
         Tree_RunLoop(node_list[i], node);
      }

      if(node->callback != NULL)
      {
         node->callback(node, e_TNE_Exit, parent);
      }
   }

}

void Tree_Run(Tree_T * tree)
{
   Tree_RunLoop(tree->root, NULL);
}

static int TreeNode_GetIndex(TreeNode_T * parent, const TreeNode_T * child)
{
   size_t i, count;
   int result;
   TreeNode_T ** node_list;

   result = -1;
   if(child != NULL)
   {
      node_list = ListMemory_Get(&parent->childeren, &count, NULL);

      for(i = 0; i < count; i ++)
      {
         if(node_list[i] == child)
         {
            result = (int)i;
            break;
         }
      }
   }
   return result;
}

int TreeNode_ChildAttach(TreeNode_T * node, TreeNode_T * child)
{
   int index;
   int result;
   index = TreeNode_GetIndex(node, child);
   if(index < 0 && child != NULL)
   {
      ListMemory_CopyAlloc(&node->childeren, child, NULL);
      if(node->callback != NULL)
      {
         node->callback(node, e_TNE_AttachedChild, child);
      }
      if(child->callback != NULL)
      {
         child->callback(child, e_TNE_AttachedToParent, node);
      }

      result = 1;
   }
   else
   {
      result = 0;
   }
   return result;
}

int TreeNode_ChildDetach(TreeNode_T * node, TreeNode_T * child)
{
   int index;
   int result;
   index = TreeNode_GetIndex(node, child);
   if(index >= 0)
   {
      ListMemory_FreeNow(&node->childeren, index);
      if(node->callback != NULL)
      {
         node->callback(node, e_TNE_DetachedChild, child);
      }
      if(child->callback != NULL)
      {
         child->callback(child, e_TNE_DetachedFromParent, node);
      }
      result = 1;
   }
   else
   {
      result = 0;
   }
   return result;
}
