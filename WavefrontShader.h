#ifndef __WAVEFRONTSHADER_H__
#define __WAVEFRONTSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"

typedef struct WavefrontShader_S WavefrontShader_T;

struct WavefrontShader_S
{
   Shader_T parent;
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

#endif // __WAVEFRONTSHADER_H__

