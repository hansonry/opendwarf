#include "WavefrontShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))

static const int attrib_data[] = {0, 1, 2};


Shader_T * WavefrontShader_Create(const char * shader_name, GLuint shader_id)
{
   WavefrontShader_T * shader;
   shader = malloc(sizeof(WavefrontShader_T));
   Shader_Init(&shader->parent, shader_name, 
                                e_ST_Wavefront, 
                                shader_id,
                                attrib_data, 3);

   shader->uniform_world             = UL("WMatrix");
   shader->uniform_world_perspective = UL("PMatrix");
   shader->uniform_texture           = UL("CSampler");
   shader->uniform_light_direction   = UL("LightDirection");
   shader->uniform_light_color       = -1; //UL("LightColor");

   RenderQueue_Init(&shader->queue_solid, sizeof(WavefrontShaderState_T));
   RenderQueue_Init(&shader->queue_transparent, sizeof(WavefrontShaderState_T));

   return (Shader_T *)shader;
}

void WavefrontShader_Destory(WavefrontShader_T * shader)
{
   RenderQueue_Destory(&shader->queue_solid);
   RenderQueue_Destory(&shader->queue_transparent);
}


void WavefrontShader_SetState(WavefrontShader_T * shader, GFXState_T * state)
{
   GFXState_SetAllMatrixUniforms(state, shader->uniform_world, shader->uniform_world_perspective);
   GFXState_SetLightSun1Uniforms(state, shader->uniform_light_direction, shader->uniform_light_color);
}

void WavefrontShader_SetTexture(WavefrontShader_T * shader, GLTexture2D_T * texture)
{
   GLTexture2D_ApplyToUniform(texture, shader->uniform_texture, GL_TEXTURE0);
}


void WavefrontShader_InsertStateToQueue(WavefrontShader_T * shader, int is_transparent)
{
   if(is_transparent)
   {
      RenderQueue_Add(&shader->queue_transparent, &shader->state);
   }
   else
   {
      RenderQueue_Add(&shader->queue_solid, &shader->state);
   }
}


