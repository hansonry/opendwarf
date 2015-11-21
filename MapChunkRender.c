#include <stdlib.h>
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "GLTexture2D.h"
#include "ShaderTool.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MapChunk.h"
#include "MapChunkRender.h"



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


static void MapChunkRender_GenMesh(MapChunkRender_T * rend)
{
      glGenBuffers(6, rend->cube_vbo);
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, UnitCube_VertexData_Front, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, UnitCube_VertexData_Right, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[2]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, UnitCube_VertexData_Back, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[3]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, UnitCube_VertexData_Left, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[4]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, UnitCube_VertexData_Top, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[5]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, UnitCube_VertexData_Bottom, GL_STATIC_DRAW);

      glGenBuffers(1, &rend->ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 4, UnitCube_Index, GL_STATIC_DRAW);
}

static void MapChunkRender_LoadResources(MapChunkRender_T * rend)
{
   GLTexture2D_Load(&rend->texture, "assets/spritesheet_tiles.png");
   rend->shader = ShaderTool_CreateShaderProgram("block.vert.glsl", 
                                                 NULL, 
                                                 "block.frag.glsl");
   rend->uniform_pmatrix = glGetUniformLocation(rend->shader, "PMatrix");
   rend->uniform_wmatrix = glGetUniformLocation(rend->shader, "WMatrix");
   rend->uniform_light_direction = glGetUniformLocation(rend->shader, "LightDirection");
   rend->uniform_csampler = glGetUniformLocation(rend->shader, "CSampler");
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
   glDeleteBuffers(6, rend->cube_vbo);
   glDeleteBuffers(1, &rend->ibo);
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

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->ibo);
   for(i = 0; i < 6; i++)
   {
      glBindBuffer(GL_ARRAY_BUFFER, rend->cube_vbo[i]);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(0));
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 3));
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 6));
      glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
   }

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}


