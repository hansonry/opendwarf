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
Position_T * Position_Subtract(Position_T * dest, const Position_T * a, const Position_T * b);
Position_T * Position_Add(Position_T * dest, const Position_T * a, const Position_T * b);
Position_T * Position_ABS(Position_T * dest, const Position_T * src);
Position_T * Position_Sign(Position_T * dest, const Position_T * src);

void         Position_ToArray(int array[3], const Position_T * src);
Position_T * Position_FromArray(Position_T * dest, const int array[3]);


#endif // __POSITION_H__

