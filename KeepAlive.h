#ifndef __KEEPALIVE_H__
#define __KEEPALIVE_H__


typedef struct KeepAlive_S      KeepAlive_T;
typedef enum   KeepAliveState_E KeepAliveState_T;

enum KeepAliveState_E
{
   e_KAS_Alive,
   e_KAS_KeptAlive,
   e_KAS_Released

};

struct KeepAlive_S
{
   int count;
   KeepAliveState_T state;
};

void KeepAlive_Init(KeepAlive_T * k_alive);

KeepAliveState_T KeepAlive_Update(KeepAlive_T * k_alive);

KeepAliveState_T KeepAlive_GetState(const KeepAlive_T * k_alive);

void KeepAlive_KeepAlive(KeepAlive_T * k_alive);

void KeepAlive_RequestRelease(KeepAlive_T * k_alive);



#endif // __KEEPALIVE_H__


