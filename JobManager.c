#include "JobManager.h"


void JobManager_Init(JobManager_T * manager, PawnList_T * pawn_list, 
                                             MapItemList_T * map_item_list, 
                                             StockPileList_T * stockpile_list)
{
   manager->pawn_list      = pawn_list;
   manager->map_item_list  = map_item_list;
   manager->stockpile_list = stockpile_list;
}

void JobManager_Destroy(JobManager_T * manager)
{
}

void JobManager_PawnLooking(JobManager_T * manager, Pawn_T * pawn)
{
}

void JobManager_PawnNotLooking(JobManager_T * manager, Pawn_T * pawn)
{
}

void JobManager_Update(JobManager_T * manager, float seconds)
{
   size_t i, k, map_item_count, stockpile_count;
   MapItem_T * map_item_list;
   Position_T * stockpile_list;

   // Find stockpiles and items that are not satified 
   map_item_list  = ListMemory_Get(&manager->map_item_list->mapitem_list, &map_item_count,  NULL);
   stockpile_list = ListMemory_Get(&manager->stockpile_list->list,        &stockpile_count, NULL);


   for(i = 0; i < map_item_count; i++)
   {

   }

}



