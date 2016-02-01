#ifndef __MAPITEMLISTRENDERER_H__
#define __MAPITEMLISTRENDERER_H__

#include "MapItemList.h"
#include "ListMemory.h"
#include "Matrix3D.h"
#include "GLTexture2D.h"
#include "WavefrontMesh.h"
#include "Shader.h"
#include "SceneGraph.h"

typedef struct MapItemListRenderer_S MapItemListRenderer_T;
struct MapItemListRenderer_S
{
   MapItemList_T * list;
   WavefrontMesh_T log_mesh;
   Shader_T * shader;
   ListMemory_T gfx_list;
   SceneGraph_T * scene_graph;
   SGNode_T * root_node;
};

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list, 
                                                            SceneGraph_T * scene_graph);
void MapItemListRenderer_Destroy(MapItemListRenderer_T * rend);

SGNode_T * MapItemListRenderer_GetNode(MapItemListRenderer_T * rend);


void MapItemListRenderer_Render(MapItemListRenderer_T * rend);


#endif // __MAPITEMLISTRENDERER_H__

