#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

static void CheckForExit(const SDL_Event *event, int * done);
static void gl_init(void);

int main(int args, char * argc[])
{
   SDL_Window  * window;
   SDL_GLContext glcontext;
   SDL_Event event;
   int done;
   int prevTicks, diffTicks, nowTicks;
   float seconds;
   
   
   
   SDL_Init(SDL_INIT_EVERYTHING);   
   window = SDL_CreateWindow("CEngine", 
                             SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 
                             800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
   
   glcontext = SDL_GL_CreateContext(window);

   gl_init();
   
   prevTicks = SDL_GetTicks();
   
   done = 0;
   while(done == 0)
   {
      while(SDL_PollEvent(&event))
      {
         CheckForExit(&event, &done);
      }
      
      nowTicks = SDL_GetTicks();
      diffTicks = nowTicks - prevTicks;
      seconds = (float)diffTicks / 1000.0f;
      prevTicks = nowTicks;
      
      glClear( GL_COLOR_BUFFER_BIT );
      
      glBegin( GL_QUADS ); 
         glVertex2f( -0.5f, -0.5f ); 
         glVertex2f( 0.5f, -0.5f ); 
         glVertex2f( 0.5f, 0.5f ); 
         glVertex2f( -0.5f, 0.5f ); 
      glEnd();
      
      SDL_GL_SwapWindow(window);
   }
   
   
   
   SDL_GL_DeleteContext(glcontext); 
   SDL_DestroyWindow(window);
   SDL_Quit();
   
   
   printf("End\n");
   return 0;
}

static void CheckForExit(const SDL_Event *event, int * done)
{
   if(event->type == SDL_QUIT)
   {
      (*done) = 1;
   }
   else if(event->type == SDL_KEYDOWN)
   {
      if(event->key.keysym.sym == SDLK_ESCAPE)
      {
         (*done) = 1;
      }
   }

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
