#include "ItemList.h"

void ItemList_Init(ItemList_T * list)
{
   ObjectList_Init(&list->item_list);
   MemoryRefSet_Init(&list->item_mem, sizeof(Item_T), (MemoryRefSet_Freeer_T)Item_Destory); 
}

void ItemList_Destroy(ItemList_T * list)
{
   ObjectList_Destory(&list->item_list);
   MemoryRefSet_Destroy(&list->item_mem);
}


void ItemList_CleanMemory(ItemList_T * list)
{
   MemoryRefSet_CheckCounts(&list->item_mem);
}


Item_T * ItemList_Add(ItemList_T * list)
{
   Item_T * item;

   item = MemoryRefSet_Allocate(&list->item_mem);
   MemoryRefSet_Keep(&list->item_mem, item);
   ObjectList_Add(&list->item_list, item);
   return item;
}


