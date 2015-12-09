#include "AStar.h"

#include <stdlib.h>


struct AStarPath_S
{
   size_t next_index_diff;
   size_t dist_from_start;
   size_t dist_from_end;
   Position_T pos;
   int is_open;

};
#define ABS(a)  (((a) < 0 )? -(a) : (a))

static size_t AStar_GuessDistance(const Position_T * a, const Position_T * b)
{
   return ABS(a->x - b->x) + ABS(a->y - b->y) + ABS(a->z - b->z);
}

static AStarPath_T * AStar_NewPath(AStar_T * as, int x, int y, int z, size_t dist_from_end, size_t * index)
{
   AStarPath_T * path;
   path = ListMemory_Allocate(&as->path_list, index);
   path->next_index_diff = 0;
   Position_Set(&path->pos, x, y, z);
   // Find path from end to start
   path->dist_from_end   = dist_from_end;
   path->dist_from_start = AStar_GuessDistance(&path->pos, &as->start);
   path->is_open = 1;
   return path;

}


void AStar_Init(AStar_T * as, MapChunk_T * map, const Position_T * start, const Position_T * end)
{  
   AStarPath_T * path; 
   as->map = map;
   ListMemory_Init(&as->path_list, sizeof(AStarPath_T), 0);
   Position_Copy(&as->start, start);
   Position_Copy(&as->end,   end);
   as->found_path = 0;

   // Find path from end to start
   (void)AStar_NewPath(as, as->end.x, as->end.y, as->end.z, 0, NULL);

}

void AStar_Destroy(AStar_T * as)
{
   ListMemory_Destory(&as->path_list);
}

Position_T * AStar_CreatePositionList(AStar_T * as, size_t * count)
{
   size_t lcount, i;
   AStarPath_T * path_list;
   size_t path_target_index, loop_index;
   Position_T * pos_list;

   path_list = ListMemory_Get(&as->path_list, NULL, NULL);

   if(as->found_path == 1)
   {
      lcount = 0;
      loop_index = as->start_index;
      while(loop_index > 0)
      {
         lcount ++;
         loop_index = loop_index - path_list[loop_index].next_index_diff;
      }

      lcount ++;

      pos_list = malloc(sizeof(Position_T) * lcount);
      if(count != NULL)
      {
         (*count) = lcount;
      }


      i = 0;
      loop_index = as->start_index;
      while(loop_index > 0)
      {
         loop_index = loop_index - path_list[loop_index].next_index_diff;
         Position_Copy(&pos_list[i], &path_list[loop_index].pos);
         i ++;
      }
      Position_Copy(&pos_list[i], &path_list[0].pos);



   }
   else
   {
      pos_list = NULL;
   }

   return pos_list;
}


static size_t AStar_ComputeDistanceFromEnd(AStarPath_T * from, const Position_T * to)
{
   return from->dist_from_end + 1;
}

static int AStar_IsValidPosition(AStar_T *as, const Position_T * pos)
{
   MapChunkTile_T map_tile;
   int output;

   if(MapChunk_InBounds(as->map, pos->x, pos->y, pos->z))
   {
      MapChunk_Get(as->map, pos->x, pos->y, pos->z, &map_tile);
      if(map_tile.topology == e_MCTT_None)
      {
         if(MapChunk_InBounds(as->map, pos->x, pos->y - 1, pos->z))
         {
            MapChunk_Get(as->map, pos->x, pos->y - 1, pos->z, &map_tile);

            if(map_tile.topology == e_MCTT_Block || 
               map_tile.topology == e_MCTT_Ramp)
            {
               output = 1;
            }
            else
            {
               output = 0;
            }
         }
         else
         {
            output = 0;
         }
      }
      else
      {
         output = 0;
      }
   }
   else
   {
      output = 0;
   }


   return output;
}

#define OFFSET_COUNT 6

static const Position_T OFFSET[OFFSET_COUNT] = 
{
   {  1,  0,  0 },
   { -1,  0,  0 },
   {  0,  1,  0 },
   {  0, -1,  0 },
   {  0,  0,  1 },
   {  0,  0, -1 }
};

static void AStar_ComputeOffset(AStar_T * as, size_t offset_index,  size_t parent_index)
{
   AStarPath_T * out;
   AStarPath_T * parent;
   AStarPath_T * path_list;
   size_t i, path_count;
   Position_T newPos;
   size_t out_index;
   size_t new_end_dist;


   path_list = ListMemory_Get(&as->path_list, &path_count, NULL);
   parent = &path_list[parent_index];

   Position_Copy(&newPos, &parent->pos);

   newPos.x += OFFSET[offset_index].x;
   newPos.y += OFFSET[offset_index].y;
   newPos.z += OFFSET[offset_index].z;

   out = NULL;
   for(i = 0; i < path_count; i++)
   {
      if(Position_IsEqual(&parent->pos, &newPos))
      {
         out = &path_list[i];
         out_index = i;
         break;
      }
   }

   
   if(out != NULL)
   {
      new_end_dist = AStar_ComputeDistanceFromEnd(parent, &out->pos);
      if(new_end_dist < out->dist_from_end)
      {
         out->dist_from_end = new_end_dist;
         out->next_index_diff = out_index - parent_index; 
      }

   }
   else if(AStar_IsValidPosition(as, &newPos))
   {

      new_end_dist = AStar_ComputeDistanceFromEnd(parent, &newPos);
      out = AStar_NewPath(as, newPos.x, newPos.y, newPos.z, new_end_dist, &out_index);
      out->next_index_diff = out_index - parent_index; 
      
   }
   

}

int AStar_Step(AStar_T * as)
{
   size_t old_list_size, i;
   size_t o_index;
   size_t lowest_path_cost, lowest_path_index;
   size_t current_path_cost;
   AStarPath_T * path_list;
   AStarPath_T * parent;
   int found_open;
   int result;

   path_list = ListMemory_Get(&as->path_list, &old_list_size, NULL);

   // Find lowest open path cost
   found_open = 0;

   for(i = 0; i < old_list_size; i++)
   {
      if(path_list[i].is_open == 1)
      {
         current_path_cost = path_list[i].dist_from_start + 
                             path_list[i].dist_from_end;
         if(found_open == 0 || 
            current_path_cost < lowest_path_cost)
         {
            found_open = 1;
            lowest_path_index = i;
            lowest_path_cost = current_path_cost;
         }
      }

   }

   // Process open if found
   if(found_open == 1)
   {
      
      parent = &path_list[lowest_path_index];
      parent->is_open = 0;
      if(Position_IsEqual(&parent->pos, &as->start))
      {
         as->found_path = 1;
         as->start_index = lowest_path_index;
         result = 0;
      }
      else
      {
         result = 1;
         for(o_index = 0; o_index < OFFSET_COUNT; o_index ++)
         {
            AStar_ComputeOffset(as, o_index, lowest_path_index);
         }
      }
   }
   else
   {
      result = 0;
   }

   return result;
}

int AStar_Run(AStar_T * as)
{
   while(AStar_Step(as));
   return as->found_path;
}

