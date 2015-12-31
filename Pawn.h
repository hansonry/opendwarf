#ifndef __PAWN_H__
#define __PAWN_H__
#include "Position.h"
#include "MapChunk.h"
#include "PawnCmd.h"
#include "Job.h"
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

void Pawn_Init(Pawn_T * pawn, MapChunk_T * map, MapItemList_T * map_item_list);
void Pawn_Destroy(Pawn_T * pawn);

void Pawn_SetComandList(Pawn_T * pawn, PawnCmd_T * cmd_list, size_t cmd_list_count);

void Pawn_Update(Pawn_T * pawn, float seconds);

void Pawn_SetJob(Pawn_T * pawn, Job_T * job);

#endif // __PAWN_H__


