#ifndef __PAWN_H__
#define __PAWN_H__

typedef struct Pawn_S Pawn_T;
struct Pawn_S
{
   int x;
   int y;
   int z;
};

Pawn_T * Pawn_Create(void);
void Pawn_Destroy(Pawn_T * pawn);


#endif // __PAWN_H__


