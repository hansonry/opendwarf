#ifndef __MAPITEMLISTRENDERER_H__
#define __MAPITEMLISTRENDERER_H__

#include "MapItemList.h"
#include "Matrix3D.h"
#include "GLTexture2D.h"
#include "WavefrontMesh.h"
#include "Shader.h"

typedef struct MapItemListRenderer_S MapItemListRenderer_T;
struct MapItemListRenderer_S
{
   MapItemList_T * list;
   WavefrontMesh_T log_mesh;
   Shader_T * shader;
};

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list);
void MapItemListRenderer_Destroy(MapItemListRenderer_T * rend);



void MapItemListRenderer_Render(MapItemListRenderer_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz);


#endif // __MAPITEMLISTRENDERER_H__

