#include <stdio.h>
#include <math.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "CEngine.h"
#include "FloatWriter.h"
#include "ShaderTool.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MatrixStack.h"

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


GLuint tri_vbo;
GLuint cube_vbo;
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
   glDeleteBuffers(1, &tri_vbo);
   glDeleteBuffers(1, &cube_vbo);
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


   glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, m_stack.matrix.data);

   glUseProgram(shader_test1);

   glBindBuffer(GL_ARRAY_BUFFER, tri_vbo);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glDrawArrays(GL_TRIANGLES, 0, 3);

   glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glDrawArrays(GL_LINE_LOOP, 0, 8);
}

static void game_input(CEngine_T * engine, SDL_Event * event)
{
}

static void gl_init(void)
{
   float vdata[8 * 3];
   float n;
   FloatWriter_T fw;

   glewInit();
   //Initialize clear color 
   glClearColor( 0.f, 0.f, 0.f, 1.f ); 

   // Init Model Data
   // TRI

   FloatWriter_Setup(&fw, vdata);
   FloatWriter_Write3F(&fw, 0,    0,    0);  
   FloatWriter_Write3F(&fw, 0.2f, 0,    0);  
   FloatWriter_Write3F(&fw, 0.2f, 0.2f, 0);  

   glGenBuffers(1, &tri_vbo);

   glBindBuffer(GL_ARRAY_BUFFER, tri_vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, vdata, GL_STATIC_DRAW);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


   // CUBE

   
   glGenBuffers(1, &cube_vbo);

   glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
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

   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 9, vdata, GL_STATIC_DRAW);
   glEnableVertexAttribArray(0);

   shader_test1 = ShaderTool_CreateShaderProgram("test1.vert.glsl", NULL, "test1.frag.glsl");

   matrix_uniform = glGetUniformLocation(shader_test1, "Matrix");

   Matrix3D_SetProjection(&projection, 30, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 100);
}
