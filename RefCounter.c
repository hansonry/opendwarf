#include <stdio.h>
#include "RefCounter.h"


void RefCounter_Init(RefCounter_T * counter)
{
   counter->count = 0;
}

void RefCounter_Keep(RefCounter_T * counter)
{
   counter->count++;
}


void RefCounter_Release(RefCounter_T * counter)
{
   counter->count --;
   if(counter->count < 0)
   {
      printf("Error: RefCounter_Release: Counter is not less than 0, count: %i\n", counter->count);
   }
}

int  RefCounter_ShouldDelete(RefCounter_T * counter)
{
   return counter->count <= 0;
}


