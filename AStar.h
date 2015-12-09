#ifndef __ASTART_H__
#define __ASTART_H__

#include "MapChunk.h"
#include "Position.h"
#include "ListMemory.h"
#include <stddef.h>

typedef struct AStar_S     AStar_T;
typedef struct AStarPath_S AStarPath_T;

struct AStar_S
{
   MapChunk_T * map;
   ListMemory_T path_list;
   Position_T start;
   Position_T end;
   size_t start_index;
   int found_path;

};

void         AStar_Init(AStar_T * as, MapChunk_T * map, const Position_T * start, const Position_T * end);
void         AStar_Destroy(AStar_T * as);

Position_T * AStar_CreatePositionList(AStar_T * as, size_t * count);
int          AStar_Run(AStar_T * as);
int          AStar_Step(AStar_T * as);




#endif // __ASTART_H__

