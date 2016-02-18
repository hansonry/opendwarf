#ifndef __REFCOUNTER_H__
#define __REFCOUNTER_H__
typedef struct RefCounter_S RefCounter_T;
struct RefCounter_S
{
   int count;
};

void RefCounter_Init(RefCounter_T * counter);

void RefCounter_Keep(RefCounter_T * counter);

void RefCounter_Release(RefCounter_T * counter);

int  RefCounter_ShouldDelete(RefCounter_T * counter);



#endif // __REFCOUNTER_H__


