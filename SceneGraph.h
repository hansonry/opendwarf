#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__
#include "ArrayList.h"
#include "Matrix3D.h"
#include "GFXState.h"

typedef struct SceneGraph_S SceneGraph_T;
typedef struct SGNode_S     SGNode_T;
typedef enum   SGNodeType_E SGNodeType_T;
typedef struct SGTrans_S    SGTrans_T;

typedef void (*SGNodeCallback_T)(SGNode_T * node, GFXState_T * state);

typedef struct SGN_Branch_S SGN_Branch_T;
typedef struct SGN_Leaf_S   SGN_Leaf_T;

struct SGTrans_S
{
   int flag_recompute;
   Matrix3D_T delta;
   Matrix3D_T final;
};



struct SGN_Leaf_S
{
   SGNodeCallback_T callback;
   void * object;
};


struct SGN_Branch_S
{
   ArrayList_T children;
};

enum SGNodeType_E
{
   e_SGNT_Branch,
   e_SGNT_Leaf,
};


struct SGNode_S
{
   SGNodeType_T type;
   SGTrans_T    trans;
   int          visible;
   union
   {
      SGN_Branch_T branch;
      SGN_Leaf_T   leaf;
   } data;
};

struct SceneGraph_S
{
   SGNode_T * root;
};


void SceneGraph_Init(SceneGraph_T * graph);
void SceneGraph_Destroy(SceneGraph_T * graph);

void SceneGraph_Render(SceneGraph_T * graph, GFXState_T * state);

void SceneGraph_SetRootNode(SceneGraph_T * graph, SGNode_T * node);


SGNode_T * SceneGraph_Node_NewBranch(SceneGraph_T * graph, const Matrix3D_T * diff);
SGNode_T * SceneGraph_Node_NewLeaf(SceneGraph_T * graph, const Matrix3D_T * diff, SGNodeCallback_T callback, void * object);
void SceneGraph_Node_SetMatrix(SGNode_T * node, const Matrix3D_T * diff);
void SceneGraph_Node_SetVisible(SGNode_T * node, int is_visible);

int SceneGraph_Node_ChildAdd(SGNode_T * node, SGNode_T * child);
int SceneGraph_Node_ChildRemove(SGNode_T * node, SGNode_T * child);




#endif // __SCENEGRAPH_H__
