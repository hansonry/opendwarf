#include "PawnCmd.h"

#include <string.h>

static void PawnCmdSystem_InitWait(PawnCmdSystem_T * sys, PawnCmdData_Wait_T * cmd);
static int PawnCmdSystem_UpdateWait(PawnCmdSystem_T * sys, PawnCmdData_Wait_T * cmd, float seconds);

static void PawnCmdSystem_InitMove(PawnCmdSystem_T * sys, PawnCmdData_Move_T * cmd);
static int PawnCmdSystem_UpdateMove(PawnCmdSystem_T * sys, PawnCmdData_Move_T * cmd, float seconds);

static void PawnCmdSystem_InitPickup(PawnCmdSystem_T * sys, PawnCmdData_Pickup_T * cmd);
static int PawnCmdSystem_UpdatePickup(PawnCmdSystem_T * sys, PawnCmdData_Pickup_T * cmd, float seconds);

static void PawnCmdSystem_InitDrop(PawnCmdSystem_T * sys, PawnCmdData_Drop_T * cmd);
static int PawnCmdSystem_UpdateDrop(PawnCmdSystem_T * sys, PawnCmdData_Drop_T * cmd, float seconds);

static float interpolate(float a, float b, float p)
{
   return a * (1 - p) + b * p;
}

void PawnCmdSystem_Init(PawnCmdSystem_T * sys, MapItemList_T * map_item_list, int x, int y, int z, float move_speed)
{
   sys->current.type = e_PCT_NULL;
   sys->state = e_PCS_Finished;
   Position_Set(&sys->position, x, y, z);
   sys->held_item = NULL;
   sys->move_speed = move_speed;
   sys->vispos_x = x;
   sys->vispos_y = y;
   sys->vispos_z = z;
   sys->map_item_list = map_item_list;

}

static void PawnCmdSystem_InitCmd(PawnCmdSystem_T * sys, PawnCmd_T * cmd)
{
   switch(cmd->type)
   {
   case e_PCT_Wait:
      PawnCmdSystem_InitWait(sys,   &cmd->data.wait);
      break;
   case e_PCT_Move:
      PawnCmdSystem_InitMove(sys,   &cmd->data.move);
      break;
   case e_PCT_Pickup:
      PawnCmdSystem_InitPickup(sys, &cmd->data.pickup);
      break;
   case e_PCT_Drop:
      PawnCmdSystem_InitDrop(sys,   &cmd->data.drop);
      break;
   case e_PCT_NULL:
   default:
      break;
   }
}

// returning 0 means Cmd has ended
static int PawnCmdSystem_UpdateCmd(PawnCmdSystem_T * sys, PawnCmd_T * cmd, float seconds)
{
   int result;

   switch(cmd->type)
   {
   case e_PCT_Wait:
      result = PawnCmdSystem_UpdateWait(sys,   &cmd->data.wait,   seconds);
      break;
   case e_PCT_Move:
      result = PawnCmdSystem_UpdateMove(sys,   &cmd->data.move,   seconds);
      break;
   case e_PCT_Pickup:
      result = PawnCmdSystem_UpdatePickup(sys, &cmd->data.pickup, seconds);
      break;
   case e_PCT_Drop:
      result = PawnCmdSystem_UpdateDrop(sys,   &cmd->data.drop,   seconds);
      break;
   case e_PCT_NULL:
   default:
      result = 0;
      break;
   }
   return result;
}


void PawnCmdSystem_Update(PawnCmdSystem_T * sys, float seconds)
{
   int result;
   if(sys->state == e_PCS_Loaded)
   {
      PawnCmdSystem_InitCmd(sys, &sys->current);
      sys->state = e_PCS_Running;
   }

   if(sys->state == e_PCS_Running)
   {
      result = PawnCmdSystem_UpdateCmd(sys, &sys->current, seconds);
      if(result == 0)
      {
         sys->state = e_PCS_Finished;
      }
   }
}

int PawnCmdSystem_IsFinished(PawnCmdSystem_T * sys)
{
   return sys->state == e_PCS_Finished;
}

int PawnCmdSystem_AttemptToSet(PawnCmdSystem_T * sys, const PawnCmd_T * new_command)
{
   int result;
   result = sys->state == e_PCS_Finished;
   if(result)
   {
      memcpy(&sys->current, new_command, sizeof(PawnCmd_T));
      sys->state = e_PCS_Loaded;
   }
   return result;
}


void PawnCmd_InitNULL(PawnCmd_T * cmd)
{
   cmd->type = e_PCT_NULL;
}

void PawnCmd_InitWait(PawnCmd_T * cmd, float time)
{
   cmd->type = e_PCT_Wait;
   cmd->data.wait.timer = time;
}

static void PawnCmdSystem_InitWait(PawnCmdSystem_T * sys, PawnCmdData_Wait_T * cmd)
{
   sys->timer = 0;
}

static int PawnCmdSystem_UpdateWait(PawnCmdSystem_T * sys, PawnCmdData_Wait_T * cmd, float seconds)
{
   int result;
   sys->timer += seconds;
   if(sys->timer < cmd->timer)
   {
      result = 1;
   }
   else
   {
      result = 0;
      sys->timer = cmd->timer;
   }
   return result;
}

void PawnCmd_InitMove(PawnCmd_T * cmd, const Position_T * target)
{
   cmd->type = e_PCT_Move;
   Position_Copy(&cmd->data.move.target, target);
}

static void PawnCmdSystem_InitMove(PawnCmdSystem_T * sys, PawnCmdData_Move_T * cmd)
{
   sys->timer = 0;
   sys->flags = 0;
}

static int PawnCmdSystem_UpdateMove(PawnCmdSystem_T * sys, PawnCmdData_Move_T * cmd, float seconds)
{
   int result;
   float p;
   sys->timer += seconds;
   if(sys->flags == 1)
   {
      result = 0;
   }
   else if(sys->timer < sys->move_speed)
   {
      result = 1;
      p = sys->timer / sys->move_speed;
      sys->vispos_x = interpolate(sys->position.x, cmd->target.x, p);
      sys->vispos_y = interpolate(sys->position.y, cmd->target.y, p);
      sys->vispos_z = interpolate(sys->position.z, cmd->target.z, p);
   }
   else
   {
      sys->timer = sys->move_speed;      
      result = 0;
      Position_Copy(&sys->position, &cmd->target);
      sys->flags = 1;
      sys->vispos_x = cmd->target.x;
      sys->vispos_y = cmd->target.y;
      sys->vispos_z = cmd->target.z;
   }
   return result;
}


void PawnCmd_InitPickup(PawnCmd_T * cmd, Item_T * item)
{
   cmd->type = e_PCT_Pickup;
   cmd->data.pickup.item = item;
}

static void PawnCmdSystem_InitPickup(PawnCmdSystem_T * sys, PawnCmdData_Pickup_T * cmd)
{
   sys->flags = 0;
}

static int PawnCmdSystem_UpdatePickup(PawnCmdSystem_T * sys, PawnCmdData_Pickup_T * cmd, float seconds)
{
   int result;
   if(sys->flags == 1)
   {
      result = 0;
   }
   else
   {
      sys->flags = 1;
      MapItemList_Remove(sys->map_item_list, cmd->item);
      sys->held_item = cmd->item;
      result = 0;
   }
   return result;
}

void PawnCmd_InitDrop(PawnCmd_T * cmd)
{
   cmd->type = e_PCT_Drop;
   cmd->data.drop.item = NULL;
}

static void PawnCmdSystem_InitDrop(PawnCmdSystem_T * sys, PawnCmdData_Drop_T * cmd)
{
}

static int PawnCmdSystem_UpdateDrop(PawnCmdSystem_T * sys, PawnCmdData_Drop_T * cmd, float seconds)
{
   int result;
   result = 0;
   return result;
}


