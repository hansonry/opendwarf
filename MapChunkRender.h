#ifndef __MAPCHUNKRENDER_H__
#define __MAPCHUNKRENDER_H__

typedef struct MapChunkRender_S MapChunkRender_T;

struct MapChunkRender_S
{
   MapChunk_T * map;
};

void MapChunkRender_Init(MapChunkRender_T * rend, MapChunk_T * map);
void MapChunkRender_Destroy(MapChunkRender_T * rend);

void MapChunkRender_Render(MapChunkRender_T * rend);



#endif // __MAPCHUNKRENDER_H__

