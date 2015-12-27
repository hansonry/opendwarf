#include "Job.h"


void Job_Init_None(Job_T * job)
{
   job->type = e_JT_None;
}

void Job_Init_PickupItem(Job_T * job, Item_T * item, const Position_T * item_pos)
{
   job->type = e_JT_PickupItem;
   job->data.pickup_item.item = item;
   Position_Copy(&job->data.pickup_item.item_pos, item_pos);
}

void Job_Init_MoveItem(Job_T * job, Item_T * item, const Position_T * item_pos, const Position_T * drop_pos)
{
   job->type = e_JT_MoveItem;
   job->data.move_item.item = item;
   Position_Copy(&job->data.move_item.item_pos, item_pos);
   Position_Copy(&job->data.move_item.drop_pos, drop_pos);
}


