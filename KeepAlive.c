#include "KeepAlive.h"

void KeepAlive_Init(KeepAlive_T * k_alive)
{
   k_alive->state = e_KAS_Alive;
   k_alive->count = 0;
}

KeepAliveState_T KeepAlive_Update(KeepAlive_T * k_alive)
{
   if(k_alive->state == e_KAS_KeptAlive)
   {
      if(k_alive->count == 0)
      {
         k_alive->state = e_KAS_Released;
      }
   }

   k_alive->count = 0;


   return k_alive->state;
}

KeepAliveState_T KeepAlive_GetState(const KeepAlive_T * k_alive)
{
   return k_alive->state;
}

void KeepAlive_KeepAlive(KeepAlive_T * k_alive)
{
   k_alive->count ++;
}

void KeepAlive_RequestRelease(KeepAlive_T * k_alive)
{
   if(k_alive->state == e_KAS_Alive)
   {
      k_alive->state = e_KAS_KeptAlive;
   }
}

