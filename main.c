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


GLMesh_T m_cube;

GLuint shader_test1;
GLint  matrix_uniform;
float angle;
Matrix3D_T projection;
MatrixStack_T m_stack;

float px, py;
float a2;

static void game_setup(CEngine_T * engine)
{
   gl_init();
   MatrixStack_Init(&m_stack);
   px = 0;
   py = 0;
   a2 = 0;
}

static void game_cleanup(CEngine_T * engine)
{
   glDeleteProgram(shader_test1);
   GLMesh_Cleanup(&m_cube);
   MatrixStack_Destroy(&m_stack);
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
   Matrix3D_SetIdentity(&matrix);

   MatrixStack_ApplyTranslation(&m_stack, px, py, 10);
   MatrixStack_ApplyYRotation(&m_stack, angle);
   MatrixStack_ApplyMatrixPre(&m_stack, &projection);


   glUseProgram(shader_test1);
   glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, m_stack.matrix.data);



   glEnableVertexAttribArray(0);
   GLMesh_Render(&m_cube, GL_TRIANGLES);
   glDisableVertexAttribArray(0);

}

static void game_input(CEngine_T * engine, SDL_Event * event)
{
}

static void gl_init(void)
{
   float vdata[8 * 3];
   unsigned int idata[12 * 3];
   unsigned int mdata[4];
   float n;
   FloatWriter_T fw;
   UIntWriter_T uiw;

   glewInit();

   //Initialize clear color 
   glClearColor( 0.f, 0.f, 0.f, 1.f ); 
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);


   // CUBE

   
   n = 0.5f;
   FloatWriter_Setup(&fw, vdata);
   FloatWriter_Write3F(&fw, -n,  n, -n);  
   FloatWriter_Write3F(&fw,  n,  n, -n);  
   FloatWriter_Write3F(&fw,  n, -n, -n);  
   FloatWriter_Write3F(&fw, -n, -n, -n);  
   
   FloatWriter_Write3F(&fw, -n,  n,  n);  
   FloatWriter_Write3F(&fw,  n,  n,  n);  
   FloatWriter_Write3F(&fw,  n, -n,  n);  
   FloatWriter_Write3F(&fw, -n, -n,  n);  

   UIntWriter_Setup(&uiw, idata);
   // front
   // 0 1
   // 3 2
   UIntWriter_Write3UI(&uiw, 0, 3, 1);
   UIntWriter_Write3UI(&uiw, 3, 2, 1);
   // right
   // 1 5
   // 2 6
   UIntWriter_Write3UI(&uiw, 1, 2, 5);
   UIntWriter_Write3UI(&uiw, 2, 6, 5);
   // back
   // 5 4
   // 6 7
   UIntWriter_Write3UI(&uiw, 5, 6, 4);
   UIntWriter_Write3UI(&uiw, 6, 7, 4);
   // right
   // 4 0
   // 7 3
   UIntWriter_Write3UI(&uiw, 4, 7, 0);
   UIntWriter_Write3UI(&uiw, 7, 3, 0);
   // bottom
   // 3 2
   // 7 6
   UIntWriter_Write3UI(&uiw, 3, 7, 2);
   UIntWriter_Write3UI(&uiw, 7, 6, 2);
   // top
   // 4 5
   // 0 1
   UIntWriter_Write3UI(&uiw, 4, 0, 5);
   UIntWriter_Write3UI(&uiw, 0, 1, 5);

   mdata[0] = 3;
   GLMesh_Init(&m_cube, mdata, 1, vdata, 8, idata, 12 * 3);
   GLMesh_MoveToGFXCard(&m_cube);


   // Shader
   shader_test1 = ShaderTool_CreateShaderProgram("test1.vert.glsl", NULL, "test1.frag.glsl");

   matrix_uniform = glGetUniformLocation(shader_test1, "Matrix");

   // Projection Matrix
   Matrix3D_SetProjection(&projection, 30, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 100);
}
