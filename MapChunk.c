#include "MapChunk.h"

#include <stdlib.h>
#include <string.h>


void MapChunk_Init(MapChunk_T * chunk, int width, int height, int depth)
{
   size_t map_size;
   map_size = width * height * depth;
   chunk->map = malloc(sizeof(MapChunkTile_T) * map_size);
   chunk->width = width;
   chunk->height = height;
   chunk->depth = depth; 
}

void MapChunk_Destroy(MapChunk_T * chunk)
{
   free(chunk->map);
   chunk->map = NULL;

}

void MapChunk_Set(MapChunk_T * chunk, int x, int y, int z, const MapChunkTile_T * tile)
{
   size_t index;
   index = x + (chunk->width * y) + (chunk->width * chunk->height * z);
   memcpy(&chunk->map[index], tile, sizeof(MapChunkTile_T)); 
}

void MapChunk_Get(MapChunk_T * chunk, int x, int y, int z, MapChunkTile_T * tile)
{
   size_t index;
   index = x + (chunk->width * y) + (chunk->width * chunk->height * z);
   memcpy(tile, &chunk->map[index], sizeof(MapChunkTile_T)); 
}

int  MapChunk_InBounds(MapChunk_T * chunk, int x, int y, int z)
{
   return x >= 0           && y >= 0            && z >= 0           &&
          x < chunk->width && y < chunk->height && z < chunk->depth;
}


void MapChunk_Fill(MapChunk_T * chunk, int x1, int y1, int z1, int x2, int y2, int z2, const MapChunkTile_T * tile)
{
   int a, b, c;

   for(a = x1; a < x2 + 1; a ++)
   {
      for(b = y1; b < y2 + 1; b ++)
      {
         for(c = z1; c < z2 + 1; c ++)
         {
            MapChunk_Set(chunk, a, b, c, tile);
         }
      }
   }
}

void MapChunk_FillAllUnknown(MapChunk_T * chunk)
{
   MapChunkTile_T tile;
   int a, b, c;
   tile.topology = e_MCTT_Unknown;
   tile.material = e_MCTM_None;

   for(a = 0; a < chunk->width; a ++)
   {
      for(b = 0; b < chunk->height; b ++)
      {
         for(c = 0; c < chunk->depth; c ++)
         {
            MapChunk_Set(chunk, a, b, c, &tile);
         }
      }
   }

}

void MapChunk_GetDimensions(MapChunk_T * chunk, int * width, int * height, int * depth)
{
   if(width != NULL)
   {
      (*width) = chunk->width;
   }

   if(height != NULL)
   {
      (*height) = chunk->height;
   }

   if(depth != NULL)
   {
      (*depth) = chunk->depth;
   }
}

void MapChunk_CopyData(MapChunk_T * dest, MapChunk_T * src, const Position_T * pos_list, size_t count)
{
   size_t i;
   MapChunkTile_T tile;

   for(i = 0; i < count; i++)
   {
      MapChunk_Get(src,  pos_list[i].x, pos_list[i].y, pos_list[i].z, &tile);
      MapChunk_Set(dest, pos_list[i].x, pos_list[i].y, pos_list[i].z, &tile);
   }

}

