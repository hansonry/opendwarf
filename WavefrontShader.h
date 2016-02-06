#ifndef __WAVEFRONTSHADER_H__
#define __WAVEFRONTSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"
#include "RenderQueue.h"

typedef struct WavefrontShader_S       WavefrontShader_T;
typedef struct WavefrontShaderState_S  WavefrontShaderState_T;

struct WavefrontShaderState_S
{
   Matrix3D_T matix_world;
   Matrix3D_T matix_world_perspective;
   GLTexture2D_T * texture;
   float light_color_r;
   float light_color_b;
   float light_color_g;
   float light_direction_x;
   float light_direction_y;
   float light_direction_z;
};

struct WavefrontShader_S
{
   Shader_T parent;
   RenderQueue_T queue_solid;
   RenderQueue_T queue_transparent;
   WavefrontShaderState_T state;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
};

Shader_T * WavefrontShader_Create(const char * shader_name, GLuint shader_id);

void WavefrontShader_Destory(WavefrontShader_T * shader);

void WavefrontShader_SetState(WavefrontShader_T * shader, GFXState_T * state);
void WavefrontShader_SetTexture(WavefrontShader_T * shader, GLTexture2D_T * texture);
void WavefrontShader_InsertStateToQueue(WavefrontShader_T * shader, int is_transparent);




#endif // __WAVEFRONTSHADER_H__

