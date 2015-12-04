#ifndef __MAPCHUNKRENDER_H__
#define __MAPCHUNKRENDER_H__

#include "MapChunk.h"
#include "Shader.h"
#include "GLTexture2D.h"
#include "Matrix3D.h"
#include "GLMesh.h"

typedef struct MapChunkRender_S MapChunkRender_T;

struct MapChunkRender_S
{
   MapChunk_T * map;
   GLMesh_T mesh;
   GLTexture2D_T * texture;
   Shader_T * shader;
};

void MapChunkRender_Init(MapChunkRender_T * rend, MapChunk_T * map);
void MapChunkRender_Destroy(MapChunkRender_T * rend);


void MapChunkRender_Render(MapChunkRender_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz);


#endif // __MAPCHUNKRENDER_H__

