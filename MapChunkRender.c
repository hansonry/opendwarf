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
#include "Resources.h"





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

static void MapChunkRender_CubeSideAjust(float * temp, const float * data, int x, int y, int z, int text_x, int text_y)
{
   float uc[4];
   float vc[4];

   uc[0] = (text_x * TILE_W) / (float)IMG_W;
   vc[0] = (IMG_H - (text_y * TILE_H)) / (float)IMG_H;

   uc[3] = uc[0] + (TILE_W / (float)IMG_W);
   vc[3] = vc[0] - (TILE_H / (float)IMG_H);

   uc[1] = uc[3];
   vc[1] = vc[0];

   uc[2] = uc[0];
   vc[2] = vc[3];

   //printf("%f %f %f %f\n", uc[0], vc[0], uc[3], vc[3]);

   memcpy(temp, data, sizeof(float) * 32);

   // UV
   temp[6] = uc[0];
   temp[7] = vc[0];

   temp[14] = uc[1];
   temp[15] = vc[1];

   temp[22] = uc[2];
   temp[23] = vc[2];

   temp[30] = uc[3];
   temp[31] = vc[3];
   // XYZ

   temp[0]  += x;
   temp[1]  += y;
   temp[2]  += z;

   temp[8]  += x;
   temp[9]  += y;
   temp[10] += z;

   temp[16] += x;
   temp[17] += y;
   temp[18] += z;

   temp[24] += x;
   temp[25] += y;
   temp[26] += z;
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
   MapChunkRender_CubeSideAjust(temp, cube_size, x, y, z, text_x, text_y);
   GLMeshBuilder_AddNVertex(builder, 4, temp);
   GLMeshBuilder_AddElementArray(builder, tris, 6);
}

typedef struct MapChunkRenderBlockTexture_S MapChunkRenderBlockTexture_T;
struct MapChunkRenderBlockTexture_S
{
   int top_x;
   int top_y;
   int side_x;
   int side_y;
   int bottom_x;
   int bottom_y;
};


static const MapChunkRenderBlockTexture_T block_texutre_data[e_MCTM_Last] = 
{
   {0, 0, 0, 0, 0, 0}, // None
   {3, 2, 9, 0, 0, 1}, // Grass
   {0, 1, 0, 1, 0, 1}, // Dirt
   {2, 6, 2, 6, 2, 6}, // Rock
   {5, 7, 4, 7, 5, 7}, // Wood
};

static void MapChunkRender_GenMesh(MapChunkRender_T * rend)
{
   unsigned int components[3];
   GLMeshBuilder_T builder;
   int x, y, z, t, width, height, depth;
   MapChunkTile_T tile;
   const MapChunkRenderBlockTexture_T * text;

   components[0] = 3;
   components[1] = 3;
   components[2] = 2;

   GLMeshBuilder_Init(&builder, components, 3);

   MapChunk_GetDimensions(rend->map, &width, &height, &depth);

   t = 0;

   for(x = 0; x < width; x++)
   {
      for(y = 0; y < height; y++)
      {
         for(z = 0; z < depth; z++)
         {
            MapChunk_Get(rend->map, x, y, z, &tile);
            if(tile.topology != e_MCTT_None)
            {
               text = &block_texutre_data[tile.material];
               MapChunkRender_AppendFace(&builder, t, UnitCube_VertexData_Front,  x, y, z, text->side_x,   text->side_y);   t++;
               MapChunkRender_AppendFace(&builder, t, UnitCube_VertexData_Right,  x, y, z, text->side_x,   text->side_y);   t++;
               MapChunkRender_AppendFace(&builder, t, UnitCube_VertexData_Back,   x, y, z, text->side_x,   text->side_y);   t++;
               MapChunkRender_AppendFace(&builder, t, UnitCube_VertexData_Left,   x, y, z, text->side_x,   text->side_y);   t++;
               MapChunkRender_AppendFace(&builder, t, UnitCube_VertexData_Top,    x, y, z, text->top_x,    text->top_y);    t++;
               MapChunkRender_AppendFace(&builder, t, UnitCube_VertexData_Bottom, x, y, z, text->bottom_x, text->bottom_y); t++;
            }
         }
      }
   }



   GLMeshBuilder_CreateGLMesh(&builder, &rend->mesh);
   GLMesh_MoveToGFXCard(&rend->mesh);

   GLMeshBuilder_Destroy(&builder);

}

static void MapChunkRender_LoadResources(MapChunkRender_T * rend)
{
   ManagerShader_T * shader_manager;
   ManagerGLTexture2D_T * texture_manager;

   shader_manager = Resource_GetShaderManager();
   texture_manager = Resources_GetTextureManager();


   rend->texture = ManagerGLTexture2D_Get(texture_manager, "assets/tiles.png");

   rend->shader = ManagerShader_Get(shader_manager, "block");
   rend->uniform_pmatrix         = glGetUniformLocation(rend->shader, "PMatrix");
   rend->uniform_wmatrix         = glGetUniformLocation(rend->shader, "WMatrix");
   rend->uniform_light_direction = glGetUniformLocation(rend->shader, "LightDirection");
   rend->uniform_csampler        = glGetUniformLocation(rend->shader, "CSampler");
}

static void MapChunkRender_FreeResources(MapChunkRender_T * rend)
{

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
   GLTexture2D_ApplyToUniform(rend->texture, rend->uniform_csampler, GL_TEXTURE0);
   

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   GLMesh_Render(&rend->mesh, GL_TRIANGLES);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}


