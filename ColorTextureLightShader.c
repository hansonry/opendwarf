#include "ColorTextureLightShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))



Shader_T * ColorTextureLightShader_Create(const char * shader_name, GLuint shader_id)
{
   ColorTextureLightShader_T * shader;
   shader = malloc(sizeof(ColorTextureLightShader_T));
   Shader_Init(&shader->parent, shader_name, 
                                e_ST_ColorTextureLight, 
                                shader_id,
                                NULL, 
                                NULL);

   shader->uniform_world             = UL("WMatrix");
   shader->uniform_world_perspective = UL("PMatrix");
   shader->uniform_texture           = UL("CSampler");
   shader->uniform_color             = UL("Color");
   shader->uniform_light_direction   = UL("LightDirection");
   shader->uniform_light_color       = UL("LightColor");

   return (Shader_T *)shader;
}
void ColorTextureLightShader_Destory(ColorTextureLightShader_T * shader);


void ColorTextureLightShader_SetState(ColorTextureLightShader_T * shader, GFXState_T * state)
{
   //GFXState_SetAllMatrixUniforms(state, shader->uniform_world, shader->uniform_world_perspective);
}

void ColorTextureLightShader_SetColor(ColorTextureLightShader_T * shader, float r, float g, float b)
{
   glUniform3f(shader->uniform_color, r, g, b);
}

void ColorTextureLightShader_SetTexture(ColorTextureLightShader_T * shader, GLTexture2D_T * texture)
{
   GLTexture2D_ApplyToUniform(texture, shader->uniform_texture, GL_TEXTURE0);
}

