#ifndef __COLORTEXTURELIGHTSHADER_H__
#define __COLORTEXTURELIGHTSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"

typedef struct ColorTextureLightShader_S ColorTextureLightShader_T;
struct ColorTextureLightShader_S
{
   Shader_T parent;
   GLint uniform_color;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
};

Shader_T * ColorTextureLightShader_Create(const char * shader_name, GLuint shader_id);

void ColorTextureLightShader_Destory(ColorTextureLightShader_T * shader);

void ColorTextureLightShader_SetState(ColorTextureLightShader_T * shader, GFXState_T * state);
void ColorTextureLightShader_SetColor(ColorTextureLightShader_T * shader, float r, float g, float b);
void ColorTextureLightShader_SetTexture(ColorTextureLightShader_T * shader, GLTexture2D_T * texture);

#endif // __COLORTEXTURELIGHTSHADER_H__

