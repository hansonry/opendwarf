#ifndef __WAVEFRONTMESH_H__
#define __WAVEFRONTMESH_H__

#include "GLMesh.h"
#include "WavefrontLoader.h"

typedef struct WavefrontMesh_S WavefrontMesh_T;
struct WavefrontMesh_S
{
   GLMesh_T mesh;

};

void WavefrontMesh_Init(WavefrontMesh_T * wmesh, WavefrontLoaderData_T * obj_data);

void WavefrontMesh_Destroy(WavefrontMesh_T * wmesh);

void WavefrontMesh_Render(WavefrontMesh_T * wmesh);

#endif // __WAVEFRONTMESH_H__

