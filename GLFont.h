#ifndef __GLFONT_H__
#define __GLFONT_H__

typedef struct GLFont_S GLFont_T;
struct GLFont_S
{
   TTF_Font * font;
};

void GLFont_Init(GLFont_T * font, const char * filename, int ptsize);
void GLFont_Destory(GLFont_T * font);

void GLFont_CreateGLTexture(GLFont_T * font, GLTexture2D_T * texture, const char * message, float r, float g, float b, float a);

#endif // __GLFONT_H__

