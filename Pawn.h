#ifndef __PAWN_H__
#define __PAWN_H__
#include "Position.h"
#include "MapChunk.h"
#include "PawnCmd.h"
#include <stddef.h>

typedef struct Pawn_S Pawn_T;

struct Pawn_S
{
   MapChunk_T * map;
   PawnCmd_T * cmd_list;
   size_t cmd_list_count;
   size_t cmd_index;
   PawnCmdSystem_T cmd_sys;
};

Pawn_T * Pawn_Create(MapChunk_T * map);
void Pawn_Destroy(Pawn_T * pawn);

void Pawn_SetComandList(Pawn_T * pawn, PawnCmd_T * cmd_list, size_t cmd_list_count);

void Pawn_Update(Pawn_T * pawn, float seconds);
#endif // __PAWN_H__


