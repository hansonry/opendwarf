#ifndef __WAVEFRONTMESH_H__
#define __WAVEFRONTMESH_H__

#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "ObjectList.h"
#include "WavefrontLoader.h"

typedef struct WavefrontMesh_S WavefrontMesh_T;
struct WavefrontMesh_S
{
   ObjectList_T mesh_texture_list;

};

void WavefrontMesh_Init(WavefrontMesh_T * wmesh, WavefrontLoaderData_T * obj_data, const char * image_file_prefix);

void WavefrontMesh_Destroy(WavefrontMesh_T * wmesh);

void WavefrontMesh_Render(WavefrontMesh_T * wmesh, GLint texture_uniform);

#endif // __WAVEFRONTMESH_H__
