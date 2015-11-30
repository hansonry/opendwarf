#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "ManagerGLTexture2D.h"

void Resources_Init(void);
void Resources_Cleanup(void);


ManagerGLTexture2D_T * Resources_GetTextureManager(void);



#endif // __RESOURCES_H__

