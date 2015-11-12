#include <stdio.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "CEngine.h"
#include "FloatWriter.h"

static void gl_init(void);

static void game_setup(CEngine_T * engine);
static void game_cleanup(CEngine_T * engine);
static void game_update(CEngine_T * engine, float seconds);
static void game_render(CEngine_T * engine);
static void game_input(CEngine_T * engine, SDL_Event * event);


int main(int args, char * argc[])
{
   CEngine_T engine;
   CEngine_Init(&engine, "CEngine", 
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


GLuint vbo;

static void game_setup(CEngine_T * engine)
{
   gl_init();
}

static void game_cleanup(CEngine_T * engine)
{
}

static void game_update(CEngine_T * engine, float seconds)
{
}

static void game_render(CEngine_T * engine)
{
   glClear( GL_COLOR_BUFFER_BIT );

   /*
   glBegin( GL_QUADS ); 
   glVertex2f( -0.5f, -0.5f ); 
   glVertex2f( 0.5f, -0.5f ); 
   glVertex2f( 0.5f, 0.5f ); 
   glVertex2f( -0.5f, 0.5f ); 
   glEnd();
   */
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void game_input(CEngine_T * engine, SDL_Event * event)
{
}

static void gl_init(void)
{
   float vdata[9];
   FloatWriter_T fw;

   //Initialize Projection Matrix 
   glewInit();
   glMatrixMode( GL_PROJECTION ); 
   glLoadIdentity(); 
   //Initialize Modelview Matrix 
   glMatrixMode( GL_MODELVIEW ); 
   glLoadIdentity(); 
   //Initialize clear color 
   glClearColor( 0.f, 0.f, 0.f, 1.f ); 

   // Init Model Data
   FloatWriter_Setup(&fw, vdata);
   FloatWriter_Write3F(&fw, 0,    0,    0);  
   FloatWriter_Write3F(&fw, 0.1f, 0,    0);  
   FloatWriter_Write3F(&fw, 0.1f, 0.1f, 0);  

   glGenBuffers(1, &vbo);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vdata, GL_STATIC_DRAW);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
