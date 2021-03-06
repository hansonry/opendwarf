#ifndef __MAPCHUNK_H__
#define __MAPCHUNK_H__

#include <stddef.h>
#include "Position.h"

typedef struct MapChunk_S             MapChunk_T;
typedef struct MapChunkTile_S         MapChunkTile_T;
typedef enum   MapChunkTileMaterial_E MapChunkTileMaterial_T;
typedef enum   MapChunkTileTopology_E MapChunkTileTopology_T;

enum MapChunkTileTopology_E
{
   e_MCTT_None,
   e_MCTT_Unknown,
   e_MCTT_Block,
   e_MCTT_Ramp,
   e_MCTT_Last
};

enum MapChunkTileMaterial_E
{
   e_MCTM_None,
   e_MCTM_Grass,
   e_MCTM_Dirt,
   e_MCTM_Rock,
   e_MCTM_Wood,
   e_MCTM_Last
};

struct MapChunkTile_S
{
   MapChunkTileTopology_T topology;
   MapChunkTileMaterial_T material;
};

struct MapChunk_S
{
   int width;
   int height;
   int depth;
   MapChunkTile_T * map;
};


void MapChunk_Init(MapChunk_T * chunk, int width, int height, int depth);
void MapChunk_Destroy(MapChunk_T * chunk);

void MapChunk_Set(MapChunk_T * chunk, int x, int y, int z, const MapChunkTile_T * tile);
void MapChunk_Get(MapChunk_T * chunk, int x, int y, int z, MapChunkTile_T * tile);

int  MapChunk_InBounds(MapChunk_T * chunk, int x, int y, int z);

void MapChunk_Fill(MapChunk_T * chunk, int x1, int y1, int z1, int x2, int y2, int z2, const MapChunkTile_T * tile);

void MapChunk_FillAllUnknown(MapChunk_T * chunk);

void MapChunk_GetDimensions(MapChunk_T * chunk, int * width, int * height, int * depth);

void MapChunk_CopyData(MapChunk_T * dest, MapChunk_T * src, const Position_T * pos_list, size_t count);


#endif // __MAPCHUNK_H__

