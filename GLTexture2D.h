#ifndef __GLTEXTURE2D_H__
#define __GLTEXTURE2D_H__

#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"

typedef struct GLTexture2D_S GLTexture2D_T;
struct GLTexture2D_S
{
   GLuint gl_id;
};

void GLTexture2D_Load(GLTexture2D_T * text, const char * filename);
void GLTexture2D_LoadID(GLTexture2D_T * text, GLuint gl_id);
void GLTexture2D_Destroy(GLTexture2D_T * text);

void GLTexture2D_ApplyToUniform(GLTexture2D_T * text, GLint uniform, GLenum texture_unit);

#endif // __GLTEXTURE2D_H__

