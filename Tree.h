#ifndef __TREE_H__
#define __TREE_H__
#include <stddef.h>
#include "ArrayList.h"
#include "ObjectList.h"

typedef struct Tree_S          Tree_T;
typedef struct TreeNode_S      TreeNode_T;
typedef enum   TreeNodeEvent_E TreeNodeEvent_T;
typedef void (*TreeNodeCallback_T)(TreeNode_T * node, TreeNodeEvent_T event, TreeNode_T * other_node);

enum TreeNodeEvent_E
{
   e_TNE_New,
   e_TNE_Destory,
   e_TNE_AttachedChild,
   e_TNE_DetachedChild,
   e_TNE_AttachedToParent,
   e_TNE_DetachedFromParent,
   e_TNE_Enter,
   e_TNE_Exit
};


struct TreeNode_S
{
   void * object;
   int owns_object;
   TreeNodeCallback_T callback;
   ArrayList_T childeren;
};

struct Tree_S
{
   TreeNode_T * root;
   ObjectList_T node_list;
};


void Tree_Init(Tree_T * tree);
void Tree_Destroy(Tree_T * tree);

TreeNode_T * Tree_NewNodeWithNewObject(Tree_T * tree, TreeNodeCallback_T callback, size_t object_size);
TreeNode_T * Tree_NewNode(Tree_T * tree, TreeNodeCallback_T callback, void * object);

void Tree_SetRootNode(Tree_T * tree, TreeNode_T * node);

void Tree_Run(Tree_T * tree);

int TreeNode_ChildAttach(TreeNode_T * node, TreeNode_T * child);
int TreeNode_ChildDetach(TreeNode_T * node, TreeNode_T * child);



#endif // __TREE_H__
