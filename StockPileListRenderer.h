#ifndef __STOCKPILELISTRENDERER_H__
#define __STOCKPILELISTRENDERER_H__
#include "StockPileList.h"
#include "Matrix3D.h"
#include "GLTexture2D.h"
#include "Shader.h"
#include "GLMesh.h"

typedef struct StockPileListRenderer_S StockPileListRenderer_T;

struct StockPileListRenderer_S
{
   StockPileList_T * list;
   GLTexture2D_T * text;
   Shader_T * shader;
   GLMesh_T mesh;
};


void StockPileListRenderer_Init(StockPileListRenderer_T * rend, StockPileList_T * list);
void StockPileListRenderer_Destroy(StockPileListRenderer_T * rend);
void StockPileListRenderer_Render(StockPileListRenderer_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz);


#endif // __STOCKPILELISTRENDERER_H__

