#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLMesh.h"
#include "UnitCube.h"

#define N 0.5f
#define U 1.0f

static const float UnitCube_VertexData[24] = 
{
   -N,  N, -N,
    N,  N, -N,
    N, -N, -N,
   -N, -N, -N,

   -N,  N,  N,
    N,  N,  N,
    N, -N,  N,
   -N, -N,  N
};

static const unsigned int UnitCube_Index[36] = 
{
   // front
   // 0 1
   // 3 2
   0, 3, 1,
   3, 2, 1,
   // right
   // 1 5
   // 2 6
   1, 2, 5,
   2, 6, 5,
   // back
   // 5 4
   // 6 7
   5, 6, 4,
   6, 7, 4,
   // right
   // 4 0
   // 7 3
   4, 7, 0,
   7, 3, 0,
   // bottom
   // 3 2
   // 7 6
   3, 7, 2,
   7, 6, 2,
   // top
   // 4 5
   // 0 1
   4, 0, 5,
   0, 1, 5

};

void UnitCube_Init(UnitCube_T * cube)
{
   unsigned int v_data[3];
   v_data[0] = 3;
   GLMesh_Init(&cube->cube, v_data, 1, UnitCube_VertexData, 8, UnitCube_Index, 36);
   GLMesh_MoveToGFXCard(&cube->cube);
}

void UnitCube_Cleanup(UnitCube_T * cube)
{
   GLMesh_Cleanup(&cube->cube);
}


void UnitCube_Render(UnitCube_T * cube)
{
   GLMesh_Render(&cube->cube, GL_TRIANGLES);
}

