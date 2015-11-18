#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "libsoil/SOIL.h"
#include "GLTexture2D.h"


void GLTexture2D_Load(GLTexture2D_T * text, const char * filename)
{

   text->gl_id = SOIL_load_OGL_texture("testImage1024.png", 
                                       SOIL_LOAD_AUTO, 
                                       SOIL_CREATE_NEW_ID, 
                                       SOIL_FLAG_MIPMAPS | 
                                       SOIL_FLAG_INVERT_Y | 
                                       SOIL_FLAG_NTSC_SAFE_RGB | 
                                       SOIL_FLAG_COMPRESS_TO_DXT);
}

void GLTexture2D_Destroy(GLTexture2D_T * text)
{
   glDeleteTextures(1, &text->gl_id);
}


void GLTexture2D_ApplyToUniform(GLTexture2D_T * text, GLint uniform, GLenum texture_unit)
{
   glActiveTexture(texture_unit);
   glBindTexture(GL_TEXTURE_2D, text->gl_id);
   glUniform1i(uniform, texture_unit - GL_TEXTURE0); // Texture unit index
}



