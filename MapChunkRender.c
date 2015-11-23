#include <stdlib.h>
#include <string.h>
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLTexture2D.h"
#include "ShaderTool.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MapChunk.h"
#include "GLMesh.h"
#include "MapChunkRender.h"
#include "GLMeshBuilder.h"





#define N 0.5f
#define U 1.0f
static const float UnitCube_VertexData_Front[32] = 
{
//  Vertex       Normal        UV
   -N,  N, -N,    0,  0, -U,   0, U,
    N,  N, -N,    0,  0, -U,   U, U,
   -N, -N, -N,    0,  0, -U,   0, 0,
    N, -N, -N,    0,  0, -U,   U, 0
};

static const float UnitCube_VertexData_Right[32] = 
{
//  Vertex       Normal        UV
    N,  N, -N,    U,  0,  0,   0, U,
    N,  N,  N,    U,  0,  0,   U, U,
    N, -N, -N,    U,  0,  0,   0, 0,
    N, -N,  N,    U,  0,  0,   U, 0
};

static const float UnitCube_VertexData_Back[32] = 
{
//  Vertex       Normal        UV
    N,  N,  N,    0,  0,  U,   0, U,
   -N,  N,  N,    0,  0,  U,   U, U,
    N, -N,  N,    0,  0,  U,   0, 0,
   -N, -N,  N,    0,  0,  U,   U, 0
};

static const float UnitCube_VertexData_Left[32] = 
{
//  Vertex       Normal        UV
   -N,  N,  N,   -U,  0,  0,   0, U,
   -N,  N, -N,   -U,  0,  0,   U, U,
   -N, -N,  N,   -U,  0,  0,   0, 0,
   -N, -N, -N,   -U,  0,  0,   U, 0
};

static const float UnitCube_VertexData_Top[32] = 
{
//  Vertex       Normal        UV
   -N,  N,  N,    0,  U,  0,   0, U,
    N,  N,  N,    0,  U,  0,   U, U,
   -N,  N, -N,    0,  U,  0,   0, 0,
    N,  N, -N,    0,  U,  0,   U, 0
};

static const float UnitCube_VertexData_Bottom[32] = 
{
//  Vertex       Normal        UV
   -N, -N, -N,    0, -U,  0,   0, U,
    N, -N, -N,    0, -U,  0,   U, U,
   -N, -N,  N,    0, -U,  0,   0, 0,
    N, -N,  N,    0, -U,  0,   U, 0
};

static const unsigned int UnitCube_Index[4] = 
{
   0, 2, 1, 3
};

#define IMG_W 1280
#define IMG_H 1152
#define TILE_W 128
#define TILE_H 128

static void MapChunkRender_UVAjust(float * temp, const float * data, int x, int y)
{
   float uc[4];
   float vc[4];

   uc[0] = (x * TILE_W) / (float)IMG_W;
   vc[0] = (IMG_H - (y * TILE_H)) / (float)IMG_H;

   uc[3] = uc[0] + (TILE_W / (float)IMG_W);
   vc[3] = vc[0] - (TILE_H / (float)IMG_H);

   uc[1] = uc[3];
   vc[1] = vc[0];

   uc[2] = uc[0];
   vc[2] = vc[3];

   //printf("%f %f %f %f\n", uc[0], vc[0], uc[3], vc[3]);

   memcpy(temp, data, sizeof(float) * 32);

   temp[6] = uc[0];
   temp[7] = vc[0];

   temp[14] = uc[1];
   temp[15] = vc[1];

   temp[22] = uc[2];
   temp[23] = vc[2];

   temp[30] = uc[3];
   temp[31] = vc[3];
};

static void MapChunkRender_AppendFace(GLMeshBuilder_T * builder, int number, const float * cube_size, int x, int y, int z, int text_x, int text_y)
{
   float temp[32];
   unsigned int tris[6];
   tris[0] = (number * 4) + 0;
   tris[1] = (number * 4) + 2;
   tris[2] = (number * 4) + 1;
   tris[3] = (number * 4) + 2;
   tris[4] = (number * 4) + 3;
   tris[5] = (number * 4) + 1;
   MapChunkRender_UVAjust(temp, cube_size, text_x, text_y);
   GLMeshBuilder_AddNVertex(builder, 4, temp);
   GLMeshBuilder_AddElementArray(builder, tris, 6);
}

static void MapChunkRender_GenMesh(MapChunkRender_T * rend)
{
   unsigned int components[3];
   GLMeshBuilder_T builder;

   components[0] = 3;
   components[1] = 3;
   components[2] = 2;

   GLMeshBuilder_Init(&builder, components, 3);


   MapChunkRender_AppendFace(&builder, 0, UnitCube_VertexData_Front,  0, 0, 0, 9, 0);
   MapChunkRender_AppendFace(&builder, 1, UnitCube_VertexData_Right,  0, 0, 0, 9, 0);
   MapChunkRender_AppendFace(&builder, 2, UnitCube_VertexData_Back,   0, 0, 0, 9, 0);
   MapChunkRender_AppendFace(&builder, 3, UnitCube_VertexData_Left,   0, 0, 0, 9, 0);
   MapChunkRender_AppendFace(&builder, 4, UnitCube_VertexData_Top,    0, 0, 0, 3, 2);
   MapChunkRender_AppendFace(&builder, 5, UnitCube_VertexData_Bottom, 0, 0, 0, 0, 1);

   GLMeshBuilder_CreateGLMesh(&builder, &rend->mesh);
   GLMesh_MoveToGFXCard(&rend->mesh);

   GLMeshBuilder_Destroy(&builder);

}

static void MapChunkRender_LoadResources(MapChunkRender_T * rend)
{
   //GLTexture2D_Load(&rend->texture, "assets/spritesheet_tiles.png");
   GLTexture2D_Load(&rend->texture, "assets/tiles.png");
   rend->shader = ShaderTool_CreateShaderProgram("block.vert.glsl", 
                                                 NULL, 
                                                 "block.frag.glsl");
   rend->uniform_pmatrix         = glGetUniformLocation(rend->shader, "PMatrix");
   rend->uniform_wmatrix         = glGetUniformLocation(rend->shader, "WMatrix");
   rend->uniform_light_direction = glGetUniformLocation(rend->shader, "LightDirection");
   rend->uniform_csampler        = glGetUniformLocation(rend->shader, "CSampler");
}

static void MapChunkRender_FreeResources(MapChunkRender_T * rend)
{
   GLTexture2D_Destroy(&rend->texture);
   glDeleteProgram(rend->shader);

}

void MapChunkRender_Init(MapChunkRender_T * rend, MapChunk_T * map)
{
   rend->map = map;
   MapChunkRender_LoadResources(rend);
   MapChunkRender_GenMesh(rend);
}



void MapChunkRender_Destroy(MapChunkRender_T * rend)
{
   GLMesh_Cleanup(&rend->mesh);
   MapChunkRender_FreeResources(rend);
}

void MapChunkRender_Render(MapChunkRender_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz)
{
   int i;
   Matrix3D_T camera;

   Matrix3D_Multiply(&camera, pers, world);

   glUseProgram(rend->shader);

   glUniform3f(rend->uniform_light_direction, lx, ly, lz);   
   glUniformMatrix4fv(rend->uniform_wmatrix,  1, GL_FALSE, world->data);
   glUniformMatrix4fv(rend->uniform_pmatrix,  1, GL_FALSE, camera.data);
   GLTexture2D_ApplyToUniform(&rend->texture, rend->uniform_csampler, GL_TEXTURE0);
   

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   GLMesh_Render(&rend->mesh, GL_TRIANGLES);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}


