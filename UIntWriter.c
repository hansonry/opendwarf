#include "UIntWriter.h"


UIntWriter_T * UIntWriter_Setup(UIntWriter_T * uiw, unsigned int * memory)
{
   uiw->memory = memory;
   uiw->index = 0;
   return uiw;
}

UIntWriter_T * UIntWriter_Write1UI(UIntWriter_T * uiw, unsigned int ui1)
{
   uiw->memory[uiw->index] = ui1;
   uiw->index ++;
   return uiw;
}
UIntWriter_T * UIntWriter_Write2UI(UIntWriter_T * uiw, unsigned int ui1, unsigned int ui2)
{
   uiw->memory[uiw->index] = ui1;
   uiw->index ++;
   uiw->memory[uiw->index] = ui2;
   uiw->index ++;
   return uiw;
}
UIntWriter_T * UIntWriter_Write3UI(UIntWriter_T * uiw, unsigned int ui1, unsigned int ui2, unsigned int ui3)
{
   uiw->memory[uiw->index] = ui1;
   uiw->index ++;
   uiw->memory[uiw->index] = ui2;
   uiw->index ++;
   uiw->memory[uiw->index] = ui3;
   uiw->index ++;
   return uiw;
}


