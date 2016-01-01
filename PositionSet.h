#ifndef __PositionSet_H__
#define __PositionSet_H__
#include "ListMemory.h"
#include "Position.h"

typedef struct PositionSet_S PositionSet_T;
struct PositionSet_S
{
   ListMemory_T list;
};


void PositionSet_Init(PositionSet_T * set);
void PositionSet_Desstroy(PositionSet_T * set);

void PositionSet_Add(PositionSet_T * set, const Position_T * pos);
void PositionSet_Clear(PositionSet_T * set);

Position_T * PositionSet_Get(PositionSet_T * set, size_t * count);


#endif // __PositionSet_H__

