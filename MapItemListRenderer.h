#ifndef __MAPITEMLISTRENDERER_H__
#define __MAPITEMLISTRENDERER_H__

#include "MapItemList.h"
#include "MatrixStack.h"
#include "GFXState.h"
#include "WavefrontMesh.h"
#include "WavefrontShader.h"


typedef struct MapItemListRenderer_S MapItemListRenderer_T;
struct MapItemListRenderer_S
{
   MapItemList_T * list;
   WavefrontMesh_T log_mesh;
   WavefrontShader_T * shader;
};

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list);
void MapItemListRenderer_Destroy(MapItemListRenderer_T * rend);



void MapItemListRenderer_Render(MapItemListRenderer_T * rend, MatrixStack_T * stack, 
                                                              GFXState_T * gfx_state);


#endif // __MAPITEMLISTRENDERER_H__

