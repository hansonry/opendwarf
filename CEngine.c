#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"
#include "CEngine.h"


void CEngine_Init(CEngine_T * engine, const char * window_title,
                  int screen_width, int screen_height,
                  CEngine_Setup_Callback_T    setup_callback,
                  CEngine_Cleanup_Callback_T  cleanup_callback,
                  CEngine_Update_Callback_T   update_callback,
                  CEngine_Render_Callback_T   render_callback,
                  CEngine_SDLInput_Callback_T sdlinput_callback,
                  int flags)
{
   engine->setup_callback    = setup_callback;
   engine->cleanup_callback  = cleanup_callback;
   engine->update_callback   = update_callback;
   engine->render_callback   = render_callback;
   engine->sdlinput_callback = sdlinput_callback;
   engine->flags             = flags;
   if(window_title == NULL)
   {
      engine->window_title = "CEngine";
   }
   else
   {
      engine->window_title = window_title;
   }
   engine->screen_width = screen_width;
   engine->screen_height = engine->screen_height;

}

void CEngine_Start(CEngine_T * engine)
{
   SDL_Window  * window;
   SDL_GLContext glcontext;
   SDL_Event event;
   int prevTicks;
   int nowTicks;
   int diffTicks;
   float seconds;


   SDL_Init(SDL_INIT_EVERYTHING); 
   TTF_Init();  

   window = SDL_CreateWindow(engine->window_title, 
                             SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 
                             800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
   
   glcontext = SDL_GL_CreateContext(window);

   if(engine->setup_callback != NULL)
   {
      engine->setup_callback(engine);
   }

   prevTicks = SDL_GetTicks();
   engine->done = 0;
   while(engine->done == 0)
   {
      while(SDL_PollEvent(&event))
      {
         if(engine->sdlinput_callback != NULL)
         {
            engine->sdlinput_callback(engine, &event);
         }
         if((engine->flags & CENGINE_FLAG_AUTOCLOSE) == CENGINE_FLAG_AUTOCLOSE)
         {

            if(event.type == SDL_QUIT)
            {
               engine->done = 1;
            }
            else if(event.type == SDL_KEYDOWN)
            {
               if(event.key.keysym.sym == SDLK_ESCAPE)
               {
                  engine->done = 1;
               }
            }
         }
      }

      nowTicks = SDL_GetTicks();
      diffTicks = nowTicks - prevTicks;
      seconds = (float)diffTicks / 1000.0f;
      prevTicks = nowTicks;

      if(engine->update_callback != NULL)
      {
         engine->update_callback(engine, seconds);
      }

      if(engine->render_callback != NULL)
      {
         engine->render_callback(engine);
      }
      SDL_GL_SwapWindow(window);
   }

   if(engine->cleanup_callback != NULL)
   {
      engine->cleanup_callback(engine);
   }

   SDL_GL_DeleteContext(glcontext); 
   SDL_DestroyWindow(window);
   SDL_Quit();
}

void CEngine_Stop(CEngine_T * engine)
{
   engine->done = 1;
}


