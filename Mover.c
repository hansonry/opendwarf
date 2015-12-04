#include "Mover.h"




void Mover_Init(Mover_T * mover, Position_T * current_pos, float timeout)
{
   mover->current_pos = current_pos;
   mover->timeout     = timeout;
   mover->timer       = 0.0f;
   mover->lx          = mover->current_pos->x;
   mover->ly          = mover->current_pos->y;
   mover->lz          = mover->current_pos->z;
   mover->is_moving   = 0;
   Position_Copy(&mover->target, mover->current_pos);

}


void Mover_MoveTo(Mover_T * mover, const Position_T * target)
{
   if(!Position_IsEqual(mover->current_pos, target))
   {
      mover->is_moving = 1;
      mover->timer = 0.0f;
      Position_Copy(&mover->target, target);
   }
}

static float interpolate(float a, float b, float p)
{
   return a * (1 - p) + b * p;
}

void Mover_Update(Mover_T * mover, float seconds)
{
   float percent;
   if(mover->is_moving == 1)
   {
      mover->timer += seconds;
      if(mover->timer < mover->timeout)
      {
         percent = mover->timer / mover->timeout;
         mover->lx = interpolate(mover->current_pos->x, mover->target.x, percent);
         mover->ly = interpolate(mover->current_pos->y, mover->target.y, percent);
         mover->lz = interpolate(mover->current_pos->z, mover->target.z, percent);
      }
      else
      {
         
         Position_Copy(mover->current_pos, &mover->target);
         mover->is_moving = 0;
         mover->lx          = mover->current_pos->x;
         mover->ly          = mover->current_pos->y;
         mover->lz          = mover->current_pos->z;
      }
   }
}


int Mover_IsMoving(const Mover_T * mover)
{
   return mover->is_moving;
}

