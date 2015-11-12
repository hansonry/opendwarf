#include "FloatWriter.h"


FloatWriter_T * FloatWriter_Setup(FloatWriter_T * fw, float * memory)
{
   fw->memory = memory;
   fw->index = 0;
   return fw;
}

FloatWriter_T * FloatWriter_Write1F(FloatWriter_T * fw, float f1)
{
   fw->memory[fw->index] = f1;
   fw->index ++;
   return fw;
}
FloatWriter_T * FloatWriter_Write2F(FloatWriter_T * fw, float f1, float f2)
{
   fw->memory[fw->index] = f1;
   fw->index ++;
   fw->memory[fw->index] = f2;
   fw->index ++;
   return fw;
}
FloatWriter_T * FloatWriter_Write3F(FloatWriter_T * fw, float f1, float f2, float f3)
{
   fw->memory[fw->index] = f1;
   fw->index ++;
   fw->memory[fw->index] = f2;
   fw->index ++;
   fw->memory[fw->index] = f3;
   fw->index ++;
   return fw;
}


