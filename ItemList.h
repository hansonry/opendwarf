#ifndef __ITEMLIST_H__
#define __ITEMLIST_H__
#include "ObjectList.h"
#include "Item.h"

typedef struct ItemList_S ItemList_T;

struct ItemList_S
{
   ObjectList_T item_list;
};

void ItemList_Init(ItemList_T * list);
void ItemList_Destroy(ItemList_T * list);

void ItemList_Update(ItemList_T * list, float seconds);


Item_T * ItemList_Add(ItemList_T * list, ItemType_T type);

#endif // __ITEMLIST_H__


