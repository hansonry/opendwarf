#ifndef __MAPITEMLISTRENDERER_H__
#define __MAPITEMLISTRENDERER_H__
#include "MapItemList.h"
#include "Matrix3D.h"

typedef struct MapItemListRenderer_S MapItemListRenderer_T;
struct MapItemListRenderer_S
{
   MapItemList_T * list;
};

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list);
void MapItemListRenderer_Destroy(MapItemListRenderer_T * rend);



void MapItemListRenderer_Render(MapItemListRenderer_T * list, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz);


#endif // __MAPITEMLISTRENDERER_H__

