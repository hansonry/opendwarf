#ifndef __PAWN_H__
#define __PAWN_H__
#include "Position.h"
#include "Mover.h"
#include "MoverControllerList.h"
#include "MapChunk.h"

typedef struct Pawn_S          Pawn_T;
typedef struct PawnCmd_S       PawnCmd_T;
typedef enum   PawnCmdType_E   PawnCmdType_T;
typedef enum   PawnCmdState_E  PawnCmdState_T;

enum PawnCmdState_E
{
   e_PCS_NoCommand,
   e_PCS_RunningCommand,
   e_PCS_FinishedCommand
};

enum PawnCmdType_E
{
   e_PCT_Wait,
   e_PCT_MoveTo,
   e_PCT_PickUp,
   e_PCT_Drop,
   e_PCT_Last
};

struct PawnCmd_S
{
   PawnCmdType_T type;
   Position_T    pos;
};



struct Pawn_S
{
   Mover_T    mover;
   Position_T pos;
   Position_T * path_list;
   MoverControllerList_T mover_ctrl;
   MapChunk_T * map;
   PawnCmd_T * cmd_list;
   PawnCmd_T   current_command;
   size_t cmd_list_count;
   size_t cmd_index;
   PawnCmdState_T cmd_state;
};

Pawn_T * Pawn_Create(MapChunk_T * map);
void Pawn_Destroy(Pawn_T * pawn);

void Pawn_SetComandList(Pawn_T * pawn, PawnCmd_T * cmd_list, size_t cmd_list_count);

void Pawn_Update(Pawn_T * pawn, float seconds);
#endif // __PAWN_H__


