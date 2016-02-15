#ifndef __STOCKPILELISTRENDERER_H__
#define __STOCKPILELISTRENDERER_H__
#include "StockPileList.h"
#include "MatrixStack.h"
#include "GFXState.h"
#include "GLTexture2D.h"
#include "ColorTextureLightShader.h"
#include "GLMesh.h"
#include "RenderQueue.h"
#include "MemoryBlock.h"

typedef struct StockPileListRenderer_S StockPileListRenderer_T;

struct StockPileListRenderer_S
{
   StockPileList_T * list;
   GLTexture2D_T * text;
   ColorTextureLightShader_T * shader;
   GLMesh_T mesh;
   MemoryBlock_T mem_block;
};


void StockPileListRenderer_Init(StockPileListRenderer_T * rend, StockPileList_T * list);
void StockPileListRenderer_Destroy(StockPileListRenderer_T * rend);
void StockPileListRenderer_Render(StockPileListRenderer_T * rend, RenderQueue_T * render_queue, 
                                                                  MatrixStack_T * stack, 
                                                                  GFXState_T    * gfx_state);


#endif // __STOCKPILELISTRENDERER_H__

