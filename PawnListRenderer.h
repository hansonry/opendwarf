#ifndef __PAWNLISTRENDERER_H__
#define __PAWNLISTRENDERER_H__
#include "PawnList.h"
#include "GLTexture2D.h"
#include "WavefrontMesh.h"
#include "WavefrontShader.h"
#include "MatrixStack.h"
#include "GFXState.h"
#include "RenderQueue.h"

typedef struct PawnListRenderer_S PawnListRenderer_T;
struct PawnListRenderer_S
{
   PawnList_T * list;
   WavefrontMesh_T pawn_mesh;
   WavefrontShader_T * shader;
};


void PawnListRenderer_Init(PawnListRenderer_T * rend, PawnList_T * list);
void PawnListRenderer_Destroy(PawnListRenderer_T * rend);


void PawnListRenderer_Render(PawnListRenderer_T * rend, RenderQueue_T * render_queue, 
                                                        MatrixStack_T * stack, 
                                                        GFXState_T    * gfx_state);

#endif // __PAWNLISTRENDERER_H__

