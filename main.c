#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "CEngine.h"

static void gl_init(void);

static void game_setup(CEngine_T * engine);
static void game_cleanup(CEngine_T * engine);
static void game_update(CEngine_T * engine, float seconds);
static void game_render(CEngine_T * engine);


int main(int args, char * argc[])
{
   CEngine_T engine;
   CEngine_Init(&engine, "CEngine", 
                         game_setup, 
                         game_cleanup, 
                         game_update, 
                         game_render, 
                         NULL,
                         CENGINE_FLAG_AUTOCLOSE);
   CEngine_Start(&engine);
      
   printf("End\n");
   return 0;
}


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

   glBegin( GL_QUADS ); 
   glVertex2f( -0.5f, -0.5f ); 
   glVertex2f( 0.5f, -0.5f ); 
   glVertex2f( 0.5f, 0.5f ); 
   glVertex2f( -0.5f, 0.5f ); 
   glEnd();
}

static void gl_init(void)
{
   //Initialize Projection Matrix 
   glMatrixMode( GL_PROJECTION ); 
   glLoadIdentity(); 
   //Initialize Modelview Matrix 
   glMatrixMode( GL_MODELVIEW ); 
   glLoadIdentity(); 
   //Initialize clear color 
   glClearColor( 0.f, 0.f, 0.f, 1.f ); 
}
