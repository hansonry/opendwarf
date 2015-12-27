#ifndef __JOB_H__
#define __JOB_H__

#include "Item.h"
#include "Position.h"

typedef enum   JobType_E        JobType_T;
typedef struct Job_S            Job_T;
typedef struct Job_PickupItem_S Job_PickupItem_T;
typedef struct Job_MoveItem_S   Job_MoveItem_T;

enum JobType_E
{
   e_JT_None,
   e_JT_PickupItem,
   e_JT_MoveItem
};

struct Job_PickupItem_S
{
   Item_T * item;
   Position_T item_pos;
};


struct Job_MoveItem_S
{
   Item_T * item;
   Position_T item_pos;
   Position_T drop_pos;
};



struct Job_S
{
   JobType_T type;
   union
   {
      Job_PickupItem_T pickup_item;
      Job_MoveItem_T   move_item;
   } data;
};



void Job_Init_None(Job_T * job);
void Job_Init_PickupItem(Job_T * job, Item_T * item, const Position_T * item_pos);
void Job_Init_MoveItem(Job_T * job, Item_T * item, const Position_T * item_pos, const Position_T * drop_pos);



#endif // __JOB_H__


