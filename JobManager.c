#include "JobManager.h"


void JobManager_Init(JobManager_T * manager)
{
   ObjectList_Init(&manager->pawn_list);
}

void JobManager_Destroy(JobManager_T * manager)
{
   ObjectList_Destory(&manager->pawn_list);
}

void JobManager_PawnLooking(JobManager_T * manager, Pawn_T * pawn)
{
   ObjectList_Add(&manager->pawn_list, pawn);
}

void JobManager_PawnNotLooking(JobManager_T * manager, Pawn_T * pawn)
{
   ObjectList_Remove(&manager->pawn_list, pawn);
}

