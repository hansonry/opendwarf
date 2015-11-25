#include <stdio.h>
#include <math.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "CEngine.h"
#include "FloatWriter.h"
#include "UIntWriter.h"
#include "ShaderTool.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MatrixStack.h"
#include "GLMesh.h"
#include "GLMeshBuilder.h"
#include "UnitCube.h"
#include "GLTexture2D.h"
#include "SDL2/SDL_ttf.h"
#include "GLFont.h"
#include "GLCam_FPS.h"
#include "MapChunk.h"
#include "MapChunkRender.h"
#include "WavefrontLoader.h"

static void gl_init(void);

static void game_setup(CEngine_T * engine);
static void game_cleanup(CEngine_T * engine);
static void game_update(CEngine_T * engine, float seconds);
static void game_render(CEngine_T * engine);
static void game_input(CEngine_T * engine, SDL_Event * event);

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600


int main(int args, char * argc[])
{
   CEngine_T engine;
   CEngine_Init(&engine, "opendwarf", SCREEN_WIDTH, SCREEN_HEIGHT,
                         game_setup, 
                         game_cleanup, 
                         game_update, 
                         game_render, 
                         game_input,
                         CENGINE_FLAG_AUTOCLOSE);
   //CEngine_Start(&engine);
   WavefrontLoader_TEST();
   printf("End\n");
   return 0;
}



// open dwarf
MapChunk_T map_chunk;
MapChunkRender_T map_chunk_render;


// other
UnitCube_T cube;

GLTexture2D_T test_text, font_text;
GLFont_T font_hanken;
GLCam_FPS_T fps_cam;
int cam_drag;
GLuint shader_test1;
GLint  pmatrix_uniform;
GLint  wmatrix_uniform;
GLint  light_direction_uniform;
GLint  csampler_uniform;
float angle;
Matrix3D_T projection;
MatrixStack_T m_stack;

float px, py;
float a2;

static void mapchunk_setup(void)
{
   MapChunkTile_T tile_air, tile_grass, tile_rock;
   tile_air.material = e_MCTM_None;
   tile_air.topology = e_MCTT_None;

   tile_grass.material = e_MCTM_Grass;
   tile_grass.topology = e_MCTT_Block;
   
   tile_rock.material = e_MCTM_Rock;
   tile_rock.topology = e_MCTT_Block;

   MapChunk_Init(&map_chunk, 5, 5, 5);

   MapChunk_Fill(&map_chunk, 0, 0, 0, 4, 4, 4, &tile_air);
   MapChunk_Fill(&map_chunk, 0, 0, 0, 4, 1, 4, &tile_grass);
   MapChunk_Set(&map_chunk, 2, 2, 2, &tile_rock);

   
   MapChunkRender_Init(&map_chunk_render, &map_chunk);
}

static void game_setup(CEngine_T * engine)
{
   gl_init();
   MatrixStack_Init(&m_stack);

   // Cube

   UnitCube_Init(&cube);

   // Shader
   shader_test1 = ShaderTool_CreateShaderProgram("test1.vert.glsl", NULL, "test1.frag.glsl");

   pmatrix_uniform = glGetUniformLocation(shader_test1, "PMatrix");
   wmatrix_uniform = glGetUniformLocation(shader_test1, "WMatrix");
   light_direction_uniform = glGetUniformLocation(shader_test1, "LightDirection");
   csampler_uniform = glGetUniformLocation(shader_test1, "CSampler");


   // Projection Matrix
   Matrix3D_SetProjection(&projection, 30, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 100);

   // Textures
   GLTexture2D_Load(&test_text, "testImage1024.png");

   // Kin
   px = 0;
   py = 0;
   a2 = 0;

   // Font Test
   GLFont_Init(&font_hanken, "Hanken-Book.ttf", 16);
   GLFont_CreateGLTexture(&font_hanken, &font_text, "Hello", 1, 0, 0, 1);

   // FPS Camera
   GLCam_FPS_Init(&fps_cam);
   cam_drag = 0;

   // open dwarf
   mapchunk_setup();
}

static void game_cleanup(CEngine_T * engine)
{
   glDeleteProgram(shader_test1);
   MatrixStack_Destroy(&m_stack);
   UnitCube_Cleanup(&cube);
   GLTexture2D_Destroy(&test_text);

   // Font Test
   GLFont_Destory(&font_hanken);
   GLTexture2D_Destroy(&font_text);

   // open dwarf
   MapChunkRender_Destroy(&map_chunk_render);
   MapChunk_Destroy(&map_chunk);
 
}

static void game_update(CEngine_T * engine, float seconds)
{
   angle = angle + 3.14f / 4.0f * seconds;
   a2 += seconds;
   px = cos(a2) * 2;
   py = sin(a2) * 2;
   if(cam_drag == 1)
   {
      int dx, dy;
      SDL_GetRelativeMouseState(&dx, &dy);
      //printf("(dx, dy): (%i, %i)\n", dx, dy);
      GLCam_FPS_Mouse(&fps_cam, dx, dy);

   }

   GLCam_FPS_Update(&fps_cam, seconds);
}

static void matrix_perspective_set(GLint uniform_world_matrix, 
                                   GLint uniform_perspective_matrix,
                                   const Matrix3D_T * world, 
                                   const Matrix3D_T * camera)
{
   Matrix3D_T temp;
   Matrix3D_Multiply(&temp, camera, world);

   glUniformMatrix4fv(uniform_world_matrix,       1, GL_FALSE, world->data);
   glUniformMatrix4fv(uniform_perspective_matrix, 1, GL_FALSE, temp.data);
}

static void game_render(CEngine_T * engine)
{
   Matrix3D_T matrix;
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   MatrixStack_Clear(&m_stack);

   GLCam_FPS_Render(&fps_cam, &m_stack);

   /*
   glBegin( GL_QUADS ); 
   glVertex2f( -0.5f, -0.5f ); 
   glVertex2f( 0.5f, -0.5f ); 
   glVertex2f( 0.5f, 0.5f ); 
   glVertex2f( -0.5f, 0.5f ); 
   glEnd();
   */



   Matrix3D_SetIdentity(&matrix);

   MatrixStack_ApplyTranslation(&m_stack, 0,  0,  10);

   matrix_perspective_set(wmatrix_uniform, pmatrix_uniform, &m_stack.matrix, &projection);


   //UnitCube_Render(&cube);
   MapChunkRender_Render(&map_chunk_render, &m_stack.matrix, &projection, 0.577f, 0.577f, -0.577f);

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);
   glEnableVertexAttribArray(3);

   glUseProgram(shader_test1);

   glUniform3f(light_direction_uniform, 0.577f, 0.577f, -0.577f);
   GLTexture2D_ApplyToUniform(&font_text, csampler_uniform, GL_TEXTURE0);

   MatrixStack_ApplyTranslation(&m_stack, px, py, 0);
   MatrixStack_ApplyYRotation(&m_stack, angle);

   matrix_perspective_set(wmatrix_uniform, pmatrix_uniform, &m_stack.matrix, &projection);
   GLTexture2D_ApplyToUniform(&test_text, csampler_uniform, GL_TEXTURE0);
   UnitCube_Render(&cube);

   // open dwarf


}

static void game_input(CEngine_T * engine, SDL_Event * event)
{
   int key_state, key_state_change;
   if(event->type == SDL_KEYDOWN)
   {
      key_state        = 1;
      key_state_change = 1;
   }
   else if(event->type == SDL_KEYUP)
   {
      key_state        = 0;
      key_state_change = 1;
   }
   else
   {
      key_state_change = 0;
   }

   if(key_state_change == 1)
   {
      if(event->key.keysym.sym == SDLK_w)      GLCam_FPS_Keyboard(&fps_cam, e_fck_forward,  key_state);
      if(event->key.keysym.sym == SDLK_s)      GLCam_FPS_Keyboard(&fps_cam, e_fck_backward, key_state);
      if(event->key.keysym.sym == SDLK_a)      GLCam_FPS_Keyboard(&fps_cam, e_fck_left,     key_state);
      if(event->key.keysym.sym == SDLK_d)      GLCam_FPS_Keyboard(&fps_cam, e_fck_right,    key_state);
      if(event->key.keysym.sym == SDLK_LSHIFT) GLCam_FPS_Keyboard(&fps_cam, e_fck_run,      key_state);
   }         


   if(event->type == SDL_MOUSEBUTTONDOWN)
   {
      cam_drag = 1;            
      SDL_GetRelativeMouseState(NULL, NULL); // Flush previous delta points
   }
   else if(event->type == SDL_MOUSEBUTTONUP)
   {
      cam_drag = 0;
   }
}


static void gl_init(void)
{

   GLMeshBuilder_T builder;

   float vdata[12];
   unsigned int mdata[4];
   float n;

   glewInit();

   //Initialize clear color 
   glClearColor( 0.f, 0.f, 0.f, 1.f ); 
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);
   glEnable(GL_DEPTH_TEST);



}



