#ifndef __UINTWRITER_H__
#define __UINTWRITER_H__

typedef struct UIntWriter_S UIntWriter_T;

struct UIntWriter_S
{
   unsigned int * memory;
   unsigned int index;
};

UIntWriter_T * UIntWriter_Setup(UIntWriter_T * uiw, unsigned int * memory);
UIntWriter_T * UIntWriter_Write1UI(UIntWriter_T * uiw, unsigned int ui1);
UIntWriter_T * UIntWriter_Write2UI(UIntWriter_T * uiw, unsigned int ui1, unsigned int ui2);
UIntWriter_T * UIntWriter_Write3UI(UIntWriter_T * uiw, unsigned int ui1, unsigned int ui2, unsigned int ui3);


#endif // __UINTWRITER_H__

