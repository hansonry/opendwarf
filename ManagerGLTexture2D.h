#ifndef __MANAGERGLTEXTURE2D_H__
#define __MANAGERGLTEXTURE2D_H__

#include "StringMap.h"
#include "ObjectList.h"
#include "GLTexture2D.h"

typedef struct ManagerGLTexture2D_S ManagerGLTexture2D_T;

struct ManagerGLTexture2D_S
{
   ObjectList_T list;
   StringMap_T  map;
};


void ManagerGLTexture2D_Init(ManagerGLTexture2D_T * manager);

void ManagerGLTexture2D_Destory(ManagerGLTexture2D_T * manager);

GLTexture2D_T * ManagerGLTexture2D_Get(ManagerGLTexture2D_T * manager, const char * filename);


#endif // __MANAGERGLTEXTURE2D_H__

