#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct Position_S Position_T;
struct Position_S
{
   int x;
   int y;
   int z;
};

Position_T * Position_Set(Position_T * pos, int x, int y, int z);
Position_T * Position_Copy(Position_T * dest, const Position_T * src);
int          Position_IsEqual(const Position_T * a, const Position_T * b);


#endif // __POSITION_H__

