#include "Item.h"

#include <stdlib.h>


Item_T * Item_Create(ItemType_T type)
{
   Item_T * item;
   item = malloc(sizeof(Item_T));
   item->type = type;
   return item;
}

void Item_Destory(Item_T * item)
{
   free(item);
}

