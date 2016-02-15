#ifndef __MAPCHUNKRENDER_H__
#define __MAPCHUNKRENDER_H__

#include "MapChunk.h"
#include "MapShader.h"
#include "GLTexture2D.h"
#include "MatrixStack.h"
#include "GFXState.h"
#include "GLMesh.h"
#include "RenderQueue.h"
#include "MemoryBlock.h"

typedef struct MapChunkRender_S MapChunkRender_T;

struct MapChunkRender_S
{
   MapChunk_T * map;
   GLMesh_T mesh;
   GLTexture2D_T * texture;
   MapShader_T * shader;
   MemoryBlock_T mem_block;
};

void MapChunkRender_Init(MapChunkRender_T * rend, MapChunk_T * map);
void MapChunkRender_Destroy(MapChunkRender_T * rend);


void MapChunkRender_Render(MapChunkRender_T * rend, RenderQueue_T * render_queue, 
                                                    MatrixStack_T * stack, 
                                                    GFXState_T * gfx_state);


#endif // __MAPCHUNKRENDER_H__

