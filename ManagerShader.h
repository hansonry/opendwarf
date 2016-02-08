#ifndef __MANAGERSHADER_H__
#define __MANAGERSHADER_H__

#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "Shader.h"
#include "ObjectList.h"
#include "StringMap.h"

typedef struct ManagerShader_S ManagerShader_T;
struct ManagerShader_S
{
   ObjectList_T list;
   StringMap_T  map;
};

void ManagerShader_Init(ManagerShader_T * manager);
void ManagerShader_Destroy(ManagerShader_T * manager);

Shader_T * ManagerShader_Get(ManagerShader_T * manager, const char * shader_id);

void ManagerShader_DrawAll(ManagerShader_T * manager);

#endif // __MANAGERSHADER_H__

