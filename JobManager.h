#ifndef __JOBMANAGER_H__
#define __JOBMANAGER_H__
#include "Pawn.h"
#include "Item.h"
#include "ObjectList.h"

typedef struct JobManager_S JobManager_T;

struct JobManager_S
{
   ObjectList_T pawn_list;
};

void JobManager_Init(JobManager_T * manager);
void JobManager_Destroy(JobManager_T * manager);

void JobManager_PawnLooking(JobManager_T * manager, Pawn_T * pawn);
void JobManager_PawnNotLooking(JobManager_T * manager, Pawn_T * pawn);




#endif // __JOBMANAGER_H__

