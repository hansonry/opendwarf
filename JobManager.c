#include "JobManager.h"


void JobManager_Init(JobManager_T * manager, PawnList_T * pawn_list, 
                                             MapItemList_T * map_item_list, 
                                             StockPileList_T * stockpile_list)
{
   manager->pawn_list      = pawn_list;
   manager->map_item_list  = map_item_list;
   manager->stockpile_list = stockpile_list;

   ArrayList_Init(&manager->unhappy_items,      sizeof(MapItem_T),  0);
   ArrayList_Init(&manager->unhappy_stockpiles, sizeof(Position_T), 0);
   ArrayList_Init(&manager->job_list,           sizeof(Job_T),      0);
}

void JobManager_Destroy(JobManager_T * manager)
{
   ArrayList_Destory(&manager->unhappy_items);
   ArrayList_Destory(&manager->unhappy_stockpiles);
   ArrayList_Destory(&manager->job_list);
}

void JobManager_PawnLooking(JobManager_T * manager, Pawn_T * pawn)
{
}

void JobManager_PawnNotLooking(JobManager_T * manager, Pawn_T * pawn)
{
}

void JobManager_Update(JobManager_T * manager, float seconds)
{
   size_t i, k;
   size_t map_item_count, stockpile_count, min_count, job_count, pawn_count;
   MapItem_T * map_item_rc;
   StockPile_T * stockpile_rc;
   MapItem_T * map_item_list;
   Position_T * stockpile_list;
   Job_T job, *job_list;
   Pawn_T * pawn;
   int found;


   // Clear Lists
   ArrayList_Clear(&manager->unhappy_items);
   ArrayList_Clear(&manager->unhappy_stockpiles);
   ArrayList_Clear(&manager->job_list);

   // Find stockpiles and items that are not satified 
   map_item_count = ObjectList_Count(&manager->map_item_list->mapitem_list);
   stockpile_count = ObjectList_Count(&manager->stockpile_list->list);


   for(i = 0; i < map_item_count; i++)
   {
      map_item_rc = ObjectList_Get(&manager->map_item_list->mapitem_list, i);
      found = 0;
      for(k = 0; k < stockpile_count; k ++)
      {
         stockpile_rc = ObjectList_Get(&manager->stockpile_list->list, k);
         if(Position_IsEqual(&map_item_rc->pos, &stockpile_rc->pos))
         {
            found = 1;
            break;
         }
      }

      if(found == 0)
      {
         ArrayList_CopyAdd(&manager->unhappy_items, map_item_rc, NULL);
      }
   }

   for(k = 0; k < stockpile_count; k++)
   {
      stockpile_rc = ObjectList_Get(&manager->stockpile_list->list, k);
      found = 0;
      for(i = 0; i < map_item_count; i ++)
      {
         map_item_rc = ObjectList_Get(&manager->map_item_list->mapitem_list, i);
         if(Position_IsEqual(&map_item_rc->pos, &stockpile_rc->pos))
         {
            found = 1;
            break;
         }
      }

      if(found == 0)
      {
         ArrayList_CopyAdd(&manager->unhappy_stockpiles, &stockpile_rc->pos, NULL);
      }
   }

   // Check new lists for possible Jobs
   map_item_list  = ArrayList_Get(&manager->unhappy_items,      &map_item_count,  NULL);
   stockpile_list = ArrayList_Get(&manager->unhappy_stockpiles, &stockpile_count, NULL);

   if(map_item_count < stockpile_count)
   {
      min_count = map_item_count;
   }
   else
   {
      min_count = stockpile_count;
   }


   for(i = 0; i < min_count; i++)
   {
      Job_MoveItem_Init(&job, map_item_list[i].item, 
                              &map_item_list[i].pos, 
                              &stockpile_list[i]);
      ArrayList_CopyAdd(&manager->job_list, &job, NULL);
   }

   // Check for bord pawns to give jobs to
   job_list = ArrayList_Get(&manager->job_list, &job_count, NULL);
   pawn_count = ObjectList_Count(&manager->pawn_list->pawn_list);

   if(job_count < pawn_count)
   {
      min_count = job_count;
   }
   else
   {
      min_count = pawn_count;
   }

   for(i = 0; i < min_count; i++)
   {
      pawn = ObjectList_Get(&manager->pawn_list->pawn_list, i);
      if(!Pawn_HasJob(pawn))
      {
         Pawn_SetJob(pawn, &job_list[i]);
      }
   }

}



