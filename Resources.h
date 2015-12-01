#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "ManagerGLTexture2D.h"
#include "ManagerShader.h"

void Resources_Init(void);
void Resources_Cleanup(void);


ManagerGLTexture2D_T * Resources_GetTextureManager(void);
ManagerShader_T * Resource_GetShaderManager(void);



#endif // __RESOURCES_H__

