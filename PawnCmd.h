#ifndef __PAWNCMD_H__
#define __PAWNCMD_H__

#include "Position.h"
#include "Item.h"
#include "MapItemList.h"

typedef enum   PawnCmdType_E        PawnCmdType_T;
typedef enum   PawnCmdState_E       PawnCmdState_T;
typedef struct PawnCmd_S            PawnCmd_T;
typedef struct PawnCmdSystem_S      PawnCmdSystem_T;
typedef struct PawnCmdData_Wait_S   PawnCmdData_Wait_T;
typedef struct PawnCmdData_Move_S   PawnCmdData_Move_T;
typedef struct PawnCmdData_Pickup_S PawnCmdData_Pickup_T;
typedef struct PawnCmdData_Drop_S   PawnCmdData_Drop_T;

enum PawnCmdState_E
{
   e_PCS_Finished,
   e_PCS_Loaded,
   e_PCS_Running
};

enum PawnCmdType_E
{
   e_PCT_NULL,
   e_PCT_Wait,
   e_PCT_Move,
   e_PCT_Pickup,
   e_PCT_Drop
};

struct PawnCmdData_Wait_S
{
   float timer;
};

struct PawnCmdData_Move_S
{
   Position_T target;
};

struct PawnCmdData_Pickup_S
{
   Item_T * item;   
};

struct PawnCmdData_Drop_S
{
   Item_T * item;
};

struct PawnCmd_S
{
   PawnCmdType_T type;
   union 
   {
      PawnCmdData_Wait_T   wait;
      PawnCmdData_Move_T   move;
      PawnCmdData_Pickup_T pickup;
      PawnCmdData_Drop_T   drop;
   } data;
};

struct PawnCmdSystem_S
{
   MapItemList_T * map_item_list;
   PawnCmd_T current;
   PawnCmdState_T state;
   Item_T * held_item;
   Position_T position;
   float timer;
   int flags;
   float move_speed;
   float vispos_x;
   float vispos_y;
   float vispos_z;
};

void PawnCmdSystem_Init(PawnCmdSystem_T * sys, MapItemList_T * map_item_list, int x, int y, int z, float move_speed);


void PawnCmdSystem_Update(PawnCmdSystem_T * sys, float seconds);

int PawnCmdSystem_IsFinished(PawnCmdSystem_T * sys);
int PawnCmdSystem_AttemptToSet(PawnCmdSystem_T * sys, const PawnCmd_T * new_command);


void PawnCmd_NULL_Init(PawnCmd_T * cmd);
void PawnCmd_Wait_Init(PawnCmd_T * cmd, float time);
void PawnCmd_Move_Init(PawnCmd_T * cmd, const Position_T * target);
void PawnCmd_Pickup_Init(PawnCmd_T * cmd, Item_T * item);
void PawnCmd_Drop_Init(PawnCmd_T * cmd);


#endif // __PAWNCMD_H__

