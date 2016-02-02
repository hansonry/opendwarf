#include "PositionSet.h"



void PositionSet_Init(PositionSet_T * set)
{
   ArrayList_Init(&set->list, sizeof(Position_T), 0);
}

void PositionSet_Desstroy(PositionSet_T * set)
{
   ArrayList_Destory(&set->list);
}

void PositionSet_Add(PositionSet_T * set, const Position_T * pos)
{
   size_t i, count;
   Position_T * pos_list;
   int found;

   pos_list = ArrayList_Get(&set->list, &count, NULL);

   found = 0;
   for(i = 0; i < count; i++)
   {
      if(Position_IsEqual(pos, &pos_list[i]))
      {
         found = 1;
         break;
      }
   }

   if(found == 0)
   {
      ArrayList_CopyAlloc(&set->list, pos, NULL);
   }
}

void PositionSet_Clear(PositionSet_T * set)
{
   ArrayList_Clear(&set->list);
}

Position_T * PositionSet_Get(PositionSet_T * set, size_t * count)
{
   return ArrayList_Get(&set->list, count, NULL);
}

