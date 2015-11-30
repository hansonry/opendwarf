#include "Resources.h"

static ManagerGLTexture2D_T texture_manager;

void Resources_Init(void)
{
   ManagerGLTexture2D_Init(&texture_manager);
}

void Resources_Cleanup(void)
{
   ManagerGLTexture2D_Destory(&texture_manager);
}


ManagerGLTexture2D_T * Resources_GetTextureManager(void)
{
   return &texture_manager;
}



