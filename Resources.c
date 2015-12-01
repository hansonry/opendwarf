#include "Resources.h"

static ManagerGLTexture2D_T texture_manager;
static ManagerShader_T      shader_manager;

void Resources_Init(void)
{
   ManagerGLTexture2D_Init(&texture_manager);
   ManagerShader_Init(&shader_manager);
}

void Resources_Cleanup(void)
{
   ManagerGLTexture2D_Destory(&texture_manager);
   ManagerShader_Destroy(&shader_manager);
}


ManagerGLTexture2D_T * Resources_GetTextureManager(void)
{
   return &texture_manager;
}


ManagerShader_T * Resource_GetShaderManager(void)
{
   return &shader_manager;
}

