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
#include "libsoil/SOIL.h"

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
   CEngine_Init(&engine, "CEngine", SCREEN_WIDTH, SCREEN_HEIGHT,
                         game_setup, 
                         game_cleanup, 
                         game_update, 
                         game_render, 
                         game_input,
                         CENGINE_FLAG_AUTOCLOSE);
   CEngine_Start(&engine);
      
   printf("End\n");
   return 0;
}


UnitCube_T cube;

GLuint tex2d;
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
   tex2d = SOIL_load_OGL_texture("testImage1024.png", 
                                 SOIL_LOAD_AUTO, 
                                 SOIL_CREATE_NEW_ID, 
                                 SOIL_FLAG_MIPMAPS | 
                                 SOIL_FLAG_INVERT_Y | 
                                 SOIL_FLAG_NTSC_SAFE_RGB | 
                                 SOIL_FLAG_COMPRESS_TO_DXT);

   // Kin
   px = 0;
   py = 0;
   a2 = 0;
}

static void game_cleanup(CEngine_T * engine)
{
   glDeleteProgram(shader_test1);
   MatrixStack_Destroy(&m_stack);
   UnitCube_Cleanup(&cube);
   glDeleteTextures(1, &tex2d);
}

static void game_update(CEngine_T * engine, float seconds)
{
   angle = angle + 3.14f / 4.0f * seconds;
   a2 += seconds;
   px = cos(a2) * 2;
   py = sin(a2) * 2;
}

static void game_render(CEngine_T * engine)
{
   Matrix3D_T matrix;
   glClear( GL_COLOR_BUFFER_BIT );
   MatrixStack_Clear(&m_stack);

   /*
   glBegin( GL_QUADS ); 
   glVertex2f( -0.5f, -0.5f ); 
   glVertex2f( 0.5f, -0.5f ); 
   glVertex2f( 0.5f, 0.5f ); 
   glVertex2f( -0.5f, 0.5f ); 
   glEnd();
   */
   glUseProgram(shader_test1);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex2d);

   glUniform3f(light_direction_uniform, 0.577f, 0.577f, -0.577f);
   glUniform1i(csampler_uniform, 0); // Texture unit number

   Matrix3D_SetIdentity(&matrix);

   MatrixStack_ApplyTranslation(&m_stack, 0,  0,  10);

   glUniformMatrix4fv(wmatrix_uniform, 1, GL_FALSE, m_stack.matrix.data);
   MatrixStack_Push(&m_stack);
   MatrixStack_ApplyMatrixPre(&m_stack, &projection);
   glUniformMatrix4fv(pmatrix_uniform, 1, GL_FALSE, m_stack.matrix.data);
   MatrixStack_Pop(&m_stack);

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);
   glEnableVertexAttribArray(3);
   UnitCube_Render(&cube);


   MatrixStack_ApplyTranslation(&m_stack, px, py, 0);
   MatrixStack_ApplyYRotation(&m_stack, angle);

   glUniformMatrix4fv(wmatrix_uniform, 1, GL_FALSE, m_stack.matrix.data);
   MatrixStack_Push(&m_stack);
   MatrixStack_ApplyMatrixPre(&m_stack, &projection);
   glUniformMatrix4fv(pmatrix_uniform, 1, GL_FALSE, m_stack.matrix.data);
   MatrixStack_Pop(&m_stack);



   UnitCube_Render(&cube);

}

static void game_input(CEngine_T * engine, SDL_Event * event)
{
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



}



