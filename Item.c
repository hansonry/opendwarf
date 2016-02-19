#include "Item.h"

#include <stdlib.h>


void Item_Init(Item_T * item, ItemType_T type)
{
   item->type = type;
   RefCounter_Init(&item->ref);
}

void Item_Destory(Item_T * item)
{
}

