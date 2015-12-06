#ifndef __ASTART_H__
#define __ASTART_H__

#include "MapChunk.h"
#include "Position.h"
#include "ListMemory.h"
#include "ObjectList.h"
#include <stddef.h>

typedef struct AStar_S     AStar_T;
typedef struct AStarPath_S AStarPath_T;

struct AStar_S
{
   MapChunk_T * map;
   ListMemory_T path_list;

};

void               AStar_Init(AStar_T * as, MapChunk_T * map, const Position_T * root);
void               AStar_Destroy(AStar_T * as);
const Position_T * AStar_GetPathFromRoot(AStar_T * as, const Position_T * dest, size_t * count);
const Position_T * AStar_GetPathToRoot(AStar_T * as, const Position_T * src, size_t * count);

void               AStar_Step(AStar_T * as);




#endif // __ASTART_H__

