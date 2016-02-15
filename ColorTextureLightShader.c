#include "ColorTextureLightShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))


static void ColorTextureLightShader_Destory(Shader_T * _shader)
{
   ColorTextureLightShader_T * shader = (ColorTextureLightShader_T*)_shader;
}

static void ColorTextureLightShader_Renderer(Shader_T * _shader, void     * _state,
                                                                 Shader_T * prev_shader,
                                                                 Shader_T * next_shader)
{
   ColorTextureLightShaderState_T * state = (ColorTextureLightShaderState_T *)_state;
   ColorTextureLightShader_T * shader = (ColorTextureLightShader_T *)_shader;

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

   glUniform3f(shader->uniform_light_color, state->light_color_r, 
                                            state->light_color_g,
                                            state->light_color_b);
   glUniform4f(shader->uniform_color, state->color_r, 
                                      state->color_g,
                                      state->color_b,
                                      state->color_a);
   glBindTexture(GL_TEXTURE_2D, state->texture->gl_id);
   GLMesh_Render(state->mesh, state->mesh_mode);

   if(_shader != next_shader)
   {
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
   }
}


Shader_T * ColorTextureLightShader_Create(const char * shader_name, GLuint shader_id)
{
   ColorTextureLightShader_T * shader;
   shader = malloc(sizeof(ColorTextureLightShader_T));
   Shader_Init(&shader->parent, shader_name, 
                                e_ST_Map, 
                                shader_id,
                                ColorTextureLightShader_Destory,
                                ColorTextureLightShader_Renderer);

   shader->uniform_world             = UL("WMatrix");
   shader->uniform_world_perspective = UL("PMatrix");
   shader->uniform_texture           = UL("CSampler");
   shader->uniform_light_direction   = UL("LightDirection");
   shader->uniform_light_color       = UL("LightColor");
   shader->uniform_color             = UL("Color");


   return (Shader_T *)shader;
}



void ColorTextureLightShader_SetState(ColorTextureLightShader_T * shader, GFXState_T * state)
{
   GFXState_SetShaderMatrix(state, &shader->state.matix_world, 
                                   &shader->state.matix_world_perspective);
   shader->state.light_direction_x = state->light_sun1.pos_x;
   shader->state.light_direction_y = state->light_sun1.pos_y;
   shader->state.light_direction_z = state->light_sun1.pos_z;

   shader->state.light_color_r = state->light_sun1.color_r;
   shader->state.light_color_g = state->light_sun1.color_g;
   shader->state.light_color_b = state->light_sun1.color_b;
}

void ColorTextureLightShader_SetColor(ColorTextureLightShader_T * shader, float color_r,
                                                                          float color_g,
                                                                          float color_b,
                                                                          float color_a)
{
   shader->state.color_r = color_r;
   shader->state.color_g = color_g;
   shader->state.color_b = color_b;
   shader->state.color_a = color_a;

}

void ColorTextureLightShader_SetMeshAndTexture(ColorTextureLightShader_T * shader, GLTexture2D_T * texture, 
                                                                                   GLMesh_T * mesh, 
                                                                                   GLenum mesh_mode)
{
   shader->state.texture = texture;
   shader->state.mesh_mode = mesh_mode;
   shader->state.mesh = mesh;
}


ColorTextureLightShaderState_T * ColorTextureLightShader_CreateState(ColorTextureLightShader_T * shader)
{

}

