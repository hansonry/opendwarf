#ifndef __ITEMLIST_H__
#define __ITEMLIST_H__
#include "ObjectList.h"
#include "Item.h"
#include "RefCounter.h"

typedef struct ItemList_S     ItemList_T;
typedef struct ItemRefCount_S ItemRefCount_T;

struct ItemRefCount_S
{
   RefCounter_T ref;
   Item_T       item;
};

struct ItemList_S
{
   ObjectList_T item_list;
};

void ItemList_Init(ItemList_T * list);
void ItemList_Destroy(ItemList_T * list);

void ItemList_CleanMemory(ItemList_T * list);


Item_T * ItemList_Add(ItemList_T * list);

#endif // __ITEMLIST_H__


