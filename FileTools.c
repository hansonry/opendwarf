#include "FileTools.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>


char * FileTools_Append(const char * base, const char * head)
{
   char * out;
   size_t lb, lh;
   lb = strlen(base);
   lh = strlen(head);
   out = malloc(sizeof(char) * (lb + lh + 1));
   memcpy(out, base, lb);
   memcpy(&out[lb], head, lh + 1);
   return out;
}


