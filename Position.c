#include "Position.h"

Position_T * Position_Set(Position_T * pos, int x, int y, int z)
{
   pos->x = x;
   pos->y = y;
   pos->z = z;
   return pos;
}

Position_T * Position_Copy(Position_T * dest, const Position_T * src)
{
   dest->x = src->x;
   dest->y = src->y;
   dest->z = src->z;
   return dest;
}

int Position_IsEqual(const Position_T * a, const Position_T * b)
{
   return a->x == b->x &&
          a->y == b->y &&
          a->z == b->z;
}

