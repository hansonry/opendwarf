#ifndef __WAVEFRONTNODE_H__
#define __WAVEFRONTNODE_H__
#include "SceneGraph.h"
#include "WavefrontShader.h"
#include "WavefrontMesh.h"

typedef struct WavefrontNode_S WavefrontNode_T;

struct WavefrontNode_S
{
   SGNode_T * node;
   WavefrontShader_T * shader;
   WavefrontMesh_T * mesh;
};

void WavefrontNode_Init(WavefrontNode_T * node, SceneGraph_T * graph,
                                                WavefrontMesh_T * mesh);

void WavefrontNode_Destroy(WavefrontNode_T * node);

SGNode_T * WavefrontNode_GetNode(WavefrontNode_T * node);




#endif // __WAVEFRONTNODE_H__
