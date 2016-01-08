#include "Resources.h"

static ManagerGLTexture2D_T texture_manager;
static ManagerShader_T      shader_manager;
static ManagerEvent_T       event_manager;

void Resources_Init(void)
{
   ManagerEvent_Init(&event_manager);
   ManagerGLTexture2D_Init(&texture_manager);
   ManagerShader_Init(&shader_manager);
}

void Resources_Cleanup(void)
{
   ManagerGLTexture2D_Destory(&texture_manager);
   ManagerShader_Destroy(&shader_manager);
   ManagerEvent_Destroy(&event_manager);
}


ManagerGLTexture2D_T * Resources_GetTextureManager(void)
{
   return &texture_manager;
}


ManagerShader_T * Resources_GetShaderManager(void)
{
   return &shader_manager;
}

ManagerEvent_T * Resources_GetEventManager(void)
{
   return &event_manager;
}

