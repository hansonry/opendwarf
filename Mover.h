#ifndef __MOVER_H__
#define __MOVER_H__

#include "Position.h"

typedef struct Mover_S Mover_T;


struct Mover_S
{
   Position_T * current_pos;
   Position_T target;
   float lx;
   float ly;
   float lz;
   float timer;
   float timeout;
   int is_moving;
};


void Mover_Init(Mover_T * mover, Position_T * current_pos, float timeout);

void Mover_MoveTo(Mover_T * mover, const Position_T * target);
int  Mover_IsMoving(const Mover_T * mover);

void Mover_Update(Mover_T * mover, float seconds);


#endif // __MOVER_H__

