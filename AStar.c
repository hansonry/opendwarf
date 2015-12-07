#include "AStar.h"

#include <stdlib.h>


struct AStarPath_S
{
   size_t next_index_diff;
   size_t dist_from_root;
   size_t difficulty;
   Position_T pos;
   int is_open;

};


static AStarPath_T * AStar_NewPath(ListMemory_T * path_list, int x, int y, int z, size_t dist_from_root, size_t * index)
{
   AStarPath_T * path;
   path = ListMemory_Allocate(path_list, index);
   path->next_index_diff = 0;
   Position_Set(&path->pos, x, y, z);
   path->dist_from_root = dist_from_root;
   path->is_open = 1;
   path->difficulty = 0;
   return path;

}


void AStar_Init(AStar_T * as, MapChunk_T * map, const Position_T * root)
{  
   AStarPath_T * path; 
   size_t index;
   as->map = map;
   ListMemory_Init(&as->path_list, sizeof(AStarPath_T), 0);

   (void)AStar_NewPath(&as->path_list, root->x, root->y, root->z, 0, &index);

}

void AStar_Destroy(AStar_T * as)
{
   ListMemory_Destory(&as->path_list);
}

Position_T * AStar_GetPathFromRoot(AStar_T * as, const Position_T * dest, size_t * count)
{
   Position_T * pos_list;
   size_t lcount;
   
   pos_list = AStar_GetPathToRoot(as, dest, &lcount);

   // TODO: Switch Around Ends

   if(count != NULL)
   {
      (*count) = lcount;
   }

   return pos_list;
}

Position_T * AStar_GetPathToRoot(AStar_T * as, const Position_T * src, size_t * count)
{
   size_t lcount, i;
   AStarPath_T * path_list;
   size_t path_list_count;
   size_t path_target_index, loop_index;
   int found_pos;
   Position_T * pos_list;

   found_pos = 0;

   path_list = ListMemory_Get(&as->path_list, &path_list_count, NULL);
   
   for(i = 0; i < path_list_count; i++)
   {
      if(Position_IsEqual(&path_list[i].pos, src))
      {
         path_target_index = i;
         found_pos = 1;
         break;
      }
   }

   if(found_pos == 1)
   {
      lcount = 0;
      loop_index = path_target_index;
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
      loop_index = path_target_index;
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

void AStar_FreePath(Position_T * path)
{
   free(path);
}

static size_t AStar_ComputeDifficulty(AStarPath_T * from, AStarPath_T * to)
{
   return from->difficulty + 1;
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
   size_t new_difficulty;


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
      new_difficulty = AStar_ComputeDifficulty(parent, out);
      if(new_difficulty < out->difficulty)
      {
         out->difficulty = new_difficulty;
         out->next_index_diff = out_index - parent_index; 
      }

   }
   else if(AStar_IsValidPosition(as, &newPos))
   {

      out = AStar_NewPath(&as->path_list, newPos.x, newPos.y, newPos.z, parent->dist_from_root + 1, &out_index);
      out->next_index_diff = out_index - parent_index; 
      out->difficulty = AStar_ComputeDifficulty(ListMemory_GetIndex(&as->path_list, parent_index), out);
      
   }
   

}

void AStar_Step(AStar_T * as)
{
   size_t p_index, old_list_size, path_count, o_index, i;
   AStarPath_T * path_list;
   AStarPath_T * parent;

   (void)ListMemory_Get(&as->path_list, &old_list_size, NULL);


   for(i = 0; i < old_list_size; i++)
   {
      p_index = i;
      parent = ListMemory_GetIndex(&as->path_list, p_index);
      if(parent->is_open == 1)
      {
         parent->is_open = 0;

         for(o_index = 0; o_index < OFFSET_COUNT; o_index ++)
         {
            AStar_ComputeOffset(as, o_index, p_index);
         }

      }



   }


}

