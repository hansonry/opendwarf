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

Position_T * Position_Subtract(Position_T * dest, const Position_T * a, const Position_T * b)
{
   dest->x = a->x - b->x;
   dest->y = a->y - b->y;
   dest->z = a->z - b->z;
   return dest;
}

Position_T * Position_Add(Position_T * dest, const Position_T * a, const Position_T * b)
{
   dest->x = a->x + b->x;
   dest->y = a->y + b->y;
   dest->z = a->z + b->z;
   return dest;
}

Position_T * Position_ABS(Position_T * dest, const Position_T * src)
{
   if(src->x < 0)
   {
      dest->x = -src->x;
   }
   else
   {
      dest->x = src->x;
   }
   if(src->y < 0)
   {
      dest->y = -src->y;
   }
   else
   {
      dest->y = src->y;
   }
   if(src->z < 0)
   {
      dest->z = -src->z;
   }
   else
   {
      dest->z = src->z;
   }
   return dest;
}

Position_T * Position_Sign(Position_T * dest, const Position_T * src)
{
   if(src->x < 0)
   {
      dest->x = -1;
   }
   else if(src->x > 0)
   {
      dest->x = 1;
   }
   else
   {
      dest->x = 0;
   }

   if(src->y < 0)
   {
      dest->y = -1;
   }
   else if(src->y > 0)
   {
      dest->y = 1;
   }
   else
   {
      dest->y = 0;
   }

   if(src->z < 0)
   {
      dest->z = -1;
   }
   else if(src->z > 0)
   {
      dest->z = 1;
   }
   else
   {
      dest->z = 0;
   }

   return dest;
}

void Position_ToArray(int array[3], const Position_T * src)
{
   array[0] = src->x;
   array[1] = src->y;
   array[2] = src->z;
}

Position_T * Position_FromArray(Position_T * dest, const int array[3])
{
   dest->x = array[0];
   dest->y = array[1];
   dest->z = array[2];
   return dest;
}

