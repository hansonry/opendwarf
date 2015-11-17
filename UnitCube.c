#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLMesh.h"
#include "UnitCube.h"

#define N 0.5f
#define U 1.0f

static const float UnitCube_VertexData_Front[44] = 
{
//  Vertex      Color       Normal        UV
   -N,  N, -N,   U, 0, 0,    0,  0, -U,   0, U,
    N,  N, -N,   0, U, 0,    0,  0, -U,   U, U,
   -N, -N, -N,   0, 0, U,    0,  0, -U,   0, 0,
    N, -N, -N,   U, U, 0,    0,  0, -U,   U, 0
};

static const float UnitCube_VertexData_Right[44] = 
{
//  Vertex      Color       Normal        UV
    N,  N, -N,   U, 0, 0,    U,  0,  0,   0, U,
    N,  N,  N,   0, U, 0,    U,  0,  0,   U, U,
    N, -N, -N,   0, 0, U,    U,  0,  0,   0, 0,
    N, -N,  N,   U, U, 0,    U,  0,  0,   U, 0
};

static const float UnitCube_VertexData_Back[44] = 
{
//  Vertex      Color       Normal        UV
    N,  N,  N,   U, 0, 0,    0,  0,  U,   0, U,
   -N,  N,  N,   0, U, 0,    0,  0,  U,   U, U,
    N, -N,  N,   0, 0, U,    0,  0,  U,   0, 0,
   -N, -N,  N,   U, U, 0,    0,  0,  U,   U, 0
};

static const float UnitCube_VertexData_Left[44] = 
{
//  Vertex      Color       Normal        UV
   -N,  N,  N,   U, 0, 0,   -U,  0,  0,   0, U,
   -N,  N, -N,   0, U, 0,   -U,  0,  0,   U, U,
   -N, -N,  N,   0, 0, U,   -U,  0,  0,   0, 0,
   -N, -N, -N,   U, U, 0,   -U,  0,  0,   U, 0
};

static const float UnitCube_VertexData_Top[44] = 
{
//  Vertex      Color       Normal        UV
   -N,  N,  N,   U, 0, 0,    0,  U,  0,   0, U,
    N,  N,  N,   0, U, 0,    0,  U,  0,   U, U,
   -N,  N, -N,   0, 0, U,    0,  U,  0,   0, 0,
    N,  N, -N,   U, U, 0,    0,  U,  0,   U, 0
};

static const float UnitCube_VertexData_Bottom[44] = 
{
//  Vertex      Color       Normal        UV
   -N, -N, -N,   U, 0, 0,    0, -U,  0,   0, U,
    N, -N, -N,   0, U, 0,    0, -U,  0,   U, U,
   -N, -N,  N,   0, 0, U,    0, -U,  0,   0, 0,
    N, -N,  N,   U, U, 0,    0, -U,  0,   U, 0
};

static const unsigned int UnitCube_Index[4] = 
{
   0, 2, 1, 3
};

void UnitCube_Init(UnitCube_T * cube)
{
   unsigned int v_data[4];
   v_data[0] = 3;
   v_data[1] = 3;
   v_data[2] = 3;
   v_data[3] = 2;
   GLMesh_Init(&cube->m_front,  v_data, 4, UnitCube_VertexData_Front,  4, UnitCube_Index, 4);
   GLMesh_MoveToGFXCard(&cube->m_front);

   GLMesh_Init(&cube->m_right,  v_data, 4, UnitCube_VertexData_Right,  4, UnitCube_Index, 4);
   GLMesh_MoveToGFXCard(&cube->m_right);

   GLMesh_Init(&cube->m_back,   v_data, 4, UnitCube_VertexData_Back,   4, UnitCube_Index, 4);
   GLMesh_MoveToGFXCard(&cube->m_back);

   GLMesh_Init(&cube->m_left,   v_data, 4, UnitCube_VertexData_Left,   4, UnitCube_Index, 4);
   GLMesh_MoveToGFXCard(&cube->m_left);

   GLMesh_Init(&cube->m_top,    v_data, 4, UnitCube_VertexData_Top,    4, UnitCube_Index, 4);
   GLMesh_MoveToGFXCard(&cube->m_top);

   GLMesh_Init(&cube->m_bottom, v_data, 4, UnitCube_VertexData_Bottom, 4, UnitCube_Index, 4);
   GLMesh_MoveToGFXCard(&cube->m_bottom);
}

void UnitCube_Cleanup(UnitCube_T * cube)
{
   GLMesh_Cleanup(&cube->m_front);
   GLMesh_Cleanup(&cube->m_right);
   GLMesh_Cleanup(&cube->m_back);
   GLMesh_Cleanup(&cube->m_left);
   GLMesh_Cleanup(&cube->m_top);
   GLMesh_Cleanup(&cube->m_bottom);
}


void UnitCube_Render(UnitCube_T * cube)
{
   GLMesh_Render(&cube->m_front, GL_TRIANGLE_STRIP);
   GLMesh_Render(&cube->m_right, GL_TRIANGLE_STRIP);
   GLMesh_Render(&cube->m_back, GL_TRIANGLE_STRIP);
   GLMesh_Render(&cube->m_left, GL_TRIANGLE_STRIP);
   GLMesh_Render(&cube->m_top, GL_TRIANGLE_STRIP);
   GLMesh_Render(&cube->m_bottom, GL_TRIANGLE_STRIP);
}

