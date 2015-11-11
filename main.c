#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

static void gl_init(void);

typedef struct SDLUtil_Data_S SDLUtil_Data_T;

static void  SDLUtil_Create(SDLUtil_Data_T * data);
static void  SDLUtil_Destroy(SDLUtil_Data_T * data);

static float SDLUtil_GetSeconds(SDLUtil_Data_T * data);

static int   SDLUtil_IsRunning(SDLUtil_Data_T * data);
static void  SDLUtil_Start(SDLUtil_Data_T * data);
static int   SDLUtil_PollEvent(SDLUtil_Data_T * data, SDL_Event * event);
static void  SDLUtil_Swap(SDLUtil_Data_T * data);

struct SDLUtil_Data_S
{
   SDL_Window  * window;
   SDL_GLContext glcontext;
   int done;
   int prevTicks;
};

int main(int args, char * argc[])
{
   SDL_Event event;
   SDLUtil_Data_T sdl_data;
   float seconds;
   
   SDLUtil_Create(&sdl_data); 
   
   gl_init();
   
   SDLUtil_Start(&sdl_data);
   while(SDLUtil_IsRunning(&sdl_data))
   {
      while(SDLUtil_PollEvent(&sdl_data, &event))
      {
      }
      
      seconds = SDLUtil_GetSeconds(&sdl_data);
      
      glClear( GL_COLOR_BUFFER_BIT );
      
      glBegin( GL_QUADS ); 
         glVertex2f( -0.5f, -0.5f ); 
         glVertex2f( 0.5f, -0.5f ); 
         glVertex2f( 0.5f, 0.5f ); 
         glVertex2f( -0.5f, 0.5f ); 
      glEnd();

      SDLUtil_Swap(&sdl_data);
      
   }
   
   
   
   SDLUtil_Destroy(&sdl_data);
   
   printf("End\n");
   return 0;
}

static void  SDLUtil_Create(SDLUtil_Data_T * data)
{

   SDL_Init(SDL_INIT_EVERYTHING);   
   data->window = SDL_CreateWindow("CEngine", 
                                   SDL_WINDOWPOS_CENTERED, 
                                   SDL_WINDOWPOS_CENTERED, 
                                    800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
   
   data->glcontext = SDL_GL_CreateContext(data->window);
}

static void  SDLUtil_Destroy(SDLUtil_Data_T * data)
{
   SDL_GL_DeleteContext(data->glcontext); 
   SDL_DestroyWindow(data->window);
   SDL_Quit();
}

static float SDLUtil_GetSeconds(SDLUtil_Data_T * data)
{
   float seconds;
   float diffTicks;
   float nowTicks;

   nowTicks = SDL_GetTicks();
   diffTicks = nowTicks - data->prevTicks;
   seconds = (float)diffTicks / 1000.0f;
   data->prevTicks = nowTicks;

   return seconds;
}

static int   SDLUtil_IsRunning(SDLUtil_Data_T * data)
{
   return !data->done;
}
static void  SDLUtil_Start(SDLUtil_Data_T * data)
{
   data->done = 0;
   data->prevTicks = SDL_GetTicks();
}
static int   SDLUtil_PollEvent(SDLUtil_Data_T * data, SDL_Event * event)
{
   int result;
   result = SDL_PollEvent(event);

   if(result)
   {
      if(event->type == SDL_QUIT)
      {
         data->done = 1;
      }
      else if(event->type == SDL_KEYDOWN)
      {
         if(event->key.keysym.sym == SDLK_ESCAPE)
         {
            data->done = 1;
         }
      }
   }
   return result;
}

static void  SDLUtil_Swap(SDLUtil_Data_T * data)
{
   SDL_GL_SwapWindow(data->window);
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
