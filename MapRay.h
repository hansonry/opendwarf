#ifndef __MAPRAY_H__
#define __MAPRAY_H__


#include "Position.h"
#include "MapChunk.h"
#include "PositionSet.h"

void MapRay_Cast(PositionSet_T * set, MapChunk_T * map, const Position_T * start, const Position_T * end); 


#endif // __MAPRAY_H__

