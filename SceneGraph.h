#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__
#include "ListMemory.h"
#include "Matrix3D.h"
#include "GFXState.h"
typedef struct SceneGraph_S SceneGraph_T;
typedef struct SGNode_S     SGNode_T;
typedef enum   SGNodeType_E SGNodeType_T;
typedef struct SGTrans_S    SGTrans_T;

typedef void (*SGMeshCallback_T)(GFXState_T * state)

typedef struct SGN_Branch_S SGN_Branch_T;
typedef struct SGN_Mesh_S   SGN_Mesh_T;

struct SGTrans_S
{
   Matrix3D_T delta;
   Matrix3D_T final;
};



struct SGN_Mesh_S
{
   SGTrans_T trans;
   SGMeshCallback_T callback;
};


struct SGN_Branch_S
{
   SGTrans_T trans;
   ListMemory_T childeren;
};

enum SGNodeType_E
{
   e_SGNT_Branch,
   e_SGNT_Leaf,
};


struct SGNode_S
{
   SGNodeType_T type;
   union
   {
      SGN_Branch_T branch;

   } data;
};

struct SceneGraph_S
{
   SGNode_T * root;
};


void SceneGraph_Init(SceneGraph_T * graph);
void SceneGraph_Destroy(SceneGraph_T * graph);

void SceneGraph_Render(SceneGraph_T * graph);

void SceneGraph_SetRootNode(SceneGraph_T * graph, SGNode_T * node);


SGN_Branch_T * SceneGraph_Branch_New(SceneGraph_T * graph, Matrix3D_T * diff);

int SceneGraph_Branch_ChildAdd(SGN_Branch_T * branch, SGNode_T * child);
int SceneGraph_Branch_ChildRemove(SGN_Branch_T * branch, SGNode_T * child);


#endif // __SCENEGRAPH_H__
