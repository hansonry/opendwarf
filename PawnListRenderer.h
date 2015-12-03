#ifndef __PAWNLISTRENDERER_H__
#define __PAWNLISTRENDERER_H__
#include "PawnList.h"
#include "Matrix3D.h"
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLTexture2D.h"
#include "WavefrontMesh.h"

typedef struct PawnListRenderer_S PawnListRenderer_T;
struct PawnListRenderer_S
{
   PawnList_T * list;
   WavefrontMesh_T pawn_mesh;
   GLuint shader;
   GLint  uniform_pmatrix;
   GLint  uniform_wmatrix;
   GLint  uniform_light_direction;
   GLint  uniform_csampler;
};


void PawnListRenderer_Init(PawnListRenderer_T * rend, PawnList_T * list);
void PawnListRenderer_Destroy(PawnListRenderer_T * rend);


void PawnListRenderer_Render(PawnListRenderer_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz);

#endif // __PAWNLISTRENDERER_H__

