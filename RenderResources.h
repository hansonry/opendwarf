#ifndef __RENDERRESOURCES_H__
#define __RENDERRESOURCES_H__
#include "ManagerGLTexture2D.h"
#include "ManagerShader.h"

ManagerGLTexture2D_T * Resources_GetTextureManager(void);
ManagerShader_T * Resources_GetShaderManager(void);

#endif // __RENDERRESOURCES_H__

