#ifndef __MAPCHUNKRENDER_H__
#define __MAPCHUNKRENDER_H__

#include "MapChunk.h"
#include "MapShader.h"
#include "GLTexture2D.h"
#include "MatrixStack.h"
#include "GFXState.h"
#include "GLMesh.h"

typedef struct MapChunkRender_S MapChunkRender_T;

struct MapChunkRender_S
{
   MapChunk_T * map;
   GLMesh_T mesh;
   GLTexture2D_T * texture;
   MapShader_T * shader;
};

void MapChunkRender_Init(MapChunkRender_T * rend, MapChunk_T * map);
void MapChunkRender_Destroy(MapChunkRender_T * rend);


void MapChunkRender_Render(MapChunkRender_T * rend, MatrixStack_T * stack, GFXState_T * gfx_state);


#endif // __MAPCHUNKRENDER_H__

