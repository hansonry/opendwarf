#ifndef __FLOATWRITER_H__
#define __FLOATWRITER_H__

typedef struct FloatWriter_S FloatWriter_T;

struct FloatWriter_S
{
   float * memory;
   unsigned int index;
};

FloatWriter_T * FloatWriter_Setup(FloatWriter_T * fw, float * memory);
FloatWriter_T * FloatWriter_Write1F(FloatWriter_T * fw, float f1);
FloatWriter_T * FloatWriter_Write2F(FloatWriter_T * fw, float f1, float f2);
FloatWriter_T * FloatWriter_Write3F(FloatWriter_T * fw, float f1, float f2, float f3);


#endif // __FLOATWRITER_H__

