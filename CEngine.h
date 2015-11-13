#ifndef __CENGINE_H__
#define __CENGINE_H__


typedef struct CEngine_S CEngine_T;
typedef void (*CEngine_Setup_Callback_T)(CEngine_T * engine);
typedef void (*CEngine_Cleanup_Callback_T)(CEngine_T * engine);
typedef void (*CEngine_Update_Callback_T)(CEngine_T * engine, float seconds);
typedef void (*CEngine_Render_Callback_T)(CEngine_T * engine);
typedef void (*CEngine_SDLInput_Callback_T)(CEngine_T * engine, SDL_Event * event);

struct CEngine_S
{
   const char *                window_title;
   CEngine_Setup_Callback_T    setup_callback;
   CEngine_Cleanup_Callback_T  cleanup_callback;
   CEngine_Update_Callback_T   update_callback;
   CEngine_Render_Callback_T   render_callback;
   CEngine_SDLInput_Callback_T sdlinput_callback;
   int screen_width;
   int screen_height;
   int flags;
   int done;
};

#define CENGINE_FLAG_AUTOCLOSE 0x01


void CEngine_Init(CEngine_T * engine, const char * window_title,
                  int screen_width, int screen_height,
                  CEngine_Setup_Callback_T    setup_callback,
                  CEngine_Cleanup_Callback_T  cleanup_callback,
                  CEngine_Update_Callback_T   update_callback,
                  CEngine_Render_Callback_T   render_callback,
                  CEngine_SDLInput_Callback_T sdlinput_callback,
                  int flags);

void CEngine_Start(CEngine_T * engine);
void CEngine_Stop(CEngine_T * engine);


#endif // __CENGINE_H__

