#ifndef __JOBMANAGER_H__
#define __JOBMANAGER_H__
#include "Job.h"
#include "PawnList.h"
#include "MapItemList.h"
#include "StockPileList.h"

typedef struct JobManager_S JobManager_T;

struct JobManager_S
{
   StockPileList_T * stockpile_list;
   MapItemList_T * map_item_list;
   PawnList_T * pawn_list;

   ListMemory_T unhappy_items;
   ListMemory_T unhappy_stockpiles;
   ListMemory_T job_list;
};

void JobManager_Init(JobManager_T * manager, PawnList_T * pawn_list, MapItemList_T * map_item_list, StockPileList_T * stockpile_list);
void JobManager_Destroy(JobManager_T * manager);

void JobManager_PawnLooking(JobManager_T * manager, Pawn_T * pawn);
void JobManager_PawnNotLooking(JobManager_T * manager, Pawn_T * pawn);

void JobManager_Update(JobManager_T * manager, float seconds);


#endif // __JOBMANAGER_H__

