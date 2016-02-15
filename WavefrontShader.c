#include "WavefrontShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))

static void WavefrontShader_Destory(Shader_T * _shader)
{
   WavefrontShader_T * shader = (WavefrontShader_T*)_shader;
}

static void WavefrontShader_Renderer(Shader_T * _shader, void     * _shader_data, 
                                                         Shader_T * prev_shader, 
                                                         Shader_T * next_shader)
{
   WavefrontShader_T * shader = (WavefrontShader_T*)_shader;
   WavefrontShaderState_T * state = (WavefrontShaderState_T*)_shader_data;

   // Setup
   if(_shader != prev_shader)
   {
      glUseProgram(shader->parent.shader_id);
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glActiveTexture(GL_TEXTURE0);
      glUniform1i(shader->uniform_texture, GL_TEXTURE0);
   }

   glUniformMatrix4fv(shader->uniform_world,             1, GL_FALSE, state->matix_world.data);
   glUniformMatrix4fv(shader->uniform_world_perspective, 1, GL_FALSE, state->matix_world_perspective.data);
   glUniform3f(shader->uniform_light_direction, state->light_direction_x, 
                                                state->light_direction_y,
                                                state->light_direction_z);
   glUniform3f(shader->uniform_light_color, state->light_color_r, 
                                            state->light_color_g,
                                            state->light_color_b);
   glBindTexture(GL_TEXTURE_2D, state->texture->gl_id);
   GLMesh_Render(state->mesh, state->mesh_mode);

   // Cleanup
   if(_shader != next_shader)
   {
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
   }
}

Shader_T * WavefrontShader_Create(const char * shader_name, GLuint shader_id)
{
   WavefrontShader_T * shader;
   shader = malloc(sizeof(WavefrontShader_T));
   Shader_Init(&shader->parent, shader_name, 
                                e_ST_Wavefront, 
                                shader_id,
                                WavefrontShader_Destory,
                                WavefrontShader_Renderer);

   shader->uniform_world             = UL("WMatrix");
   shader->uniform_world_perspective = UL("PMatrix");
   shader->uniform_texture           = UL("CSampler");
   shader->uniform_light_direction   = UL("LightDirection");
   shader->uniform_light_color       = -1; //UL("LightColor");


   return (Shader_T *)shader;
}



void WavefrontShaderState_SetGFXState(WavefrontShaderState_T * state, GFXState_T * gfx_state)
{
   GFXState_SetShaderMatrix(gfx_state, &state->matix_world, 
                                       &state->matix_world_perspective);
   state->light_direction_x = gfx_state->light_sun1.pos_x;
   state->light_direction_y = gfx_state->light_sun1.pos_y;
   state->light_direction_z = gfx_state->light_sun1.pos_z;

   state->light_color_r = gfx_state->light_sun1.color_r;
   state->light_color_g = gfx_state->light_sun1.color_g;
   state->light_color_b = gfx_state->light_sun1.color_b;
}

void WavefrontShaderState_SetMeshAndTexture(WavefrontShaderState_T * state, GLTexture2D_T * texture, 
                                                                            GLMesh_T * mesh, 
                                                                            GLenum mesh_mode)
{
   state->texture   = texture;
   state->mesh_mode = mesh_mode;
   state->mesh      = mesh;
}



