#ifndef __ITEM_H__
#define __ITEM_H__
#include "KeepAlive.h"

typedef enum   ItemType_E ItemType_T;
typedef struct Item_S     Item_T;

enum ItemType_E
{
   e_IT_Log,
   e_IT_Rock
};

struct Item_S
{
   ItemType_T   type;
   KeepAlive_T  k_alive;
};

void Item_Init(Item_T * item, ItemType_T type);

void Item_Destory(Item_T * item);


#endif // __ITEM_H__

