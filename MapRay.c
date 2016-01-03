#include "MapRay.h"
//#include <stdio.h>

static int MapRay_CheckPoint(PositionSet_T * set, MapChunk_T * map, const int * ipos)
{
   int continue_check;
   Position_T pos;
   MapChunkTile_T tile;

   Position_FromArray(&pos, ipos);

   if(MapChunk_InBounds(map, pos.x, pos.y, pos.z))
   {
      MapChunk_Get(map, pos.x, pos.y, pos.z, &tile);

      PositionSet_Add(set, &pos);
      //printf("(%i, %i, %i)\n", pos.x, pos.y, pos.z);

      if(tile.topology == e_MCTT_Block)
      {
         continue_check = 0;
      }
      else
      {
         continue_check = 1;
      }
   }
   else
   {
      continue_check = 0;
   }

   return continue_check;
}


void MapRay_Cast(PositionSet_T * set, MapChunk_T * map, const Position_T * start, const Position_T * end)
{
   Position_T delta;
   Position_T abs_delta;
   Position_T sign_delta;
   float error[2];
   float error_delta[2];
   int continue_check;
   int c_start, c_end;
   int ipos[3];
   int isign_delta[3];
   int index0, index1, index2;
   int ran_check;


   Position_Subtract(&delta, end, start);
   Position_ABS(&abs_delta, &delta);
   Position_Sign(&sign_delta, &delta);
   error[0] = 0;
   error[1] = 0;

   Position_ToArray(ipos, start);
   Position_ToArray(isign_delta, &sign_delta);


   


   if(abs_delta.x >= abs_delta.y && abs_delta.x >= abs_delta.z)
   {
      error_delta[0] = abs_delta.y / (float)abs_delta.x;
      error_delta[1] = abs_delta.z / (float)abs_delta.x;
      c_start        = start->x;
      c_end          = end->x;
      index0         = 0;
      index1         = 1;
      index2         = 2;
   }
   else if(abs_delta.y >= abs_delta.x && abs_delta.y >= abs_delta.z)
   {
      error_delta[0] = abs_delta.x / (float)abs_delta.y;
      error_delta[1] = abs_delta.z / (float)abs_delta.y;
      c_start        = start->y;
      c_end          = end->y;
      index0         = 1;
      index1         = 0;
      index2         = 2;
   }
   else if(abs_delta.z >= abs_delta.x && abs_delta.z >= abs_delta.y)
   {
      error_delta[0] = abs_delta.y / (float)abs_delta.z;
      error_delta[1] = abs_delta.x / (float)abs_delta.z;
      c_start        = start->z;
      c_end          = end->z;
      index0         = 2;
      index1         = 1;
      index2         = 0;
   }
   else
   {
      // Do Nothing
      c_start = start->x;
      c_end   = start->x;
      index0  = 0;
   }


   continue_check = 1;
   for(ipos[index0] = c_start; 
       ipos[index0] != c_end; 
       ipos[index0] += isign_delta[index0])
   {
      ran_check = 0;
      if(continue_check == 0)
      {
         break;
      }
      else
      {
         error[0] += error_delta[0];
         error[1] += error_delta[1];

         while((error[0] >= 0.5f || error[1] >= 0.5f) && 
               continue_check == 1)
         {
            if(error[0] > error[1])
            {
               error[0] -= 1.0f;
               ipos[index1] += isign_delta[index1];
            }
            else
            {
               error[1] -= 1.0f;
               ipos[index2] += isign_delta[index2];
            }

            continue_check = MapRay_CheckPoint(set, map, ipos);
            ran_check = 1;

         }
         if(ran_check == 0)
         {
            ran_check = 1;
            continue_check = MapRay_CheckPoint(set, map, ipos);
         }
      }
   }

   if(continue_check == 1)
   {
      (void)MapRay_CheckPoint(set, map, ipos);
   }

}


