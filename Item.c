#include "Item.h"

#include <stdlib.h>


void Item_Init(Item_T * item, ItemType_T type)
{
   item->type = type;
   KeepAlive_Init(&item->k_alive);
}

void Item_Destory(Item_T * item)
{
}

