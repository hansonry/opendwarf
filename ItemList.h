#ifndef __ITEMLIST_H__
#define __ITEMLIST_H__
#include "MemoryRefSet.h"
#include "ObjectList.h"
#include "Item.h"

typedef struct ItemList_S ItemList_T;
struct ItemList_S
{
   ObjectList_T item_list;
   MemoryRefSet_T item_mem;
};

void ItemList_Init(ItemList_T * list);
void ItemList_Destroy(ItemList_T * list);

void ItemList_CleanMemory(ItemList_T * list);


Item_T * ItemList_Add(ItemList_T * list);

#endif // __ITEMLIST_H__


