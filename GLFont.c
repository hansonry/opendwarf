#include <stdio.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "GLTexture2D.h"
#include "SDL2/SDL_ttf.h"
#include "GLFont.h"




void GLFont_Init(GLFont_T * font, const char * filename, int ptsize)
{
   font->font = TTF_OpenFont(filename, ptsize);
   if(font->font == NULL)
   {
      printf("Error: GLFont_Init Failed to load font %s at size %i\n", filename, ptsize);
   }
}

void GLFont_Destory(GLFont_T * font)
{
   if(font->font != NULL)
   {
      TTF_CloseFont(font->font);
      font->font = NULL;
   }
}

void GLFont_CreateGLTexture(GLFont_T * font, GLTexture2D_T * texture, const char * message, float r, float g, float b, float a)
{
   SDL_Surface *surf;
   SDL_Color color;
   GLint text_id;
   int colors;
   GLenum format;

   color.r = (Uint8)(0xFF * r);
   color.g = (Uint8)(0xFF * g);
   color.b = (Uint8)(0xFF * b);
   color.a = (Uint8)(0xFF * a);

   glEnable(GL_BLEND); // Enable Blending, otherwise nothing will work
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   surf = TTF_RenderText_Blended(font->font, message, color);
   if(surf == NULL)
   {
      printf("Error: GLFont_CreateGLTexture Failed to create: %s\n", message);      
      printf("       Error Text: %s\n", TTF_GetError());
   }
   else
   {
      colors = surf->format->BytesPerPixel;
      if(colors == 4)
      {
         if(surf->format->Rmask == 0x000000ff)
         {
            format = GL_RGBA;
         }
         else
         {
            format = GL_BGRA;
         }
      }
      else
      {
         if(surf->format->Rmask == 0x000000ff)
         {
            format = GL_RGB;
         }
         else
         {
            format = GL_BGR;
         }
      }

      

      glGenTextures(1, &text_id);
      glBindTexture(GL_TEXTURE_2D, text_id);
      //printf("w: %i, h: %i\n", surf->w, surf->h);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, colors, surf->w, surf->h, 0,
                   format, GL_UNSIGNED_BYTE, surf->pixels);


      //glGenerateMipmap(GL_TEXTURE_2D);

      GLTexture2D_LoadID(texture, text_id);


      SDL_FreeSurface(surf);
   }
}


