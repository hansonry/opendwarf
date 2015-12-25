#ifndef __JOBMANAGER_H__
#define __JOBMANAGER_H__
#include "Pawn.h"
#include "Item.h"


typedef struct JobManager_S JobManager_T;

struct JobManager_S
{
   int thing;
};

void JobManager_Init(JobManager_T * manager);
void JobManager_Destroy(JobManager_T * manager);

void JobManager_PawnLooking(Pawn_T * pawn);
void JobManager_PawnNotLooking(Pawn_T * pawn);




#endif // __JOBMANAGER_H__

