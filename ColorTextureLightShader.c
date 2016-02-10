#include "ColorTextureLightShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))


static void ColorTextureLightShader_Destory(Shader_T * _shader)
{
   ColorTextureLightShader_T * shader = (ColorTextureLightShader_T*)_shader;
   RenderQueue_Destory(&shader->queue_solid);
   RenderQueue_Destory(&shader->queue_transparent);
}

static void ColorTextureLightShader_RenderQueue(ColorTextureLightShader_T * shader, RenderQueue_T * queue)
{
   ColorTextureLightShaderState_T state;
   glUseProgram(shader->parent.shader_id);
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);
   glActiveTexture(GL_TEXTURE0);

   glUniform1i(shader->uniform_texture, GL_TEXTURE0);
   while(RenderQueue_Pop(queue, &state))
   {

      glUniformMatrix4fv(shader->uniform_world,             1, GL_FALSE, state.matix_world.data);
      glUniformMatrix4fv(shader->uniform_world_perspective, 1, GL_FALSE, state.matix_world_perspective.data);
      glUniform3f(shader->uniform_light_direction, state.light_direction_x, 
                                                   state.light_direction_y,
                                                   state.light_direction_z);
      glUniform3f(shader->uniform_light_color, state.light_color_r, 
                                               state.light_color_g,
                                               state.light_color_b);

      glUniform3f(shader->uniform_light_color, state.light_color_r, 
                                               state.light_color_g,
                                               state.light_color_b);
      glUniform4f(shader->uniform_color, state.color_r, 
                                         state.color_g,
                                         state.color_b,
                                         state.color_a);
      glBindTexture(GL_TEXTURE_2D, state.texture->gl_id);
      GLMesh_Render(state.mesh, state.mesh_mode);
   }
   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}

static void ColorTextureLightShader_Renderer(Shader_T * _shader, ShaderPass_T pass)
{
   ColorTextureLightShader_T * shader = (ColorTextureLightShader_T*)_shader;
   if(pass == e_SP_Solid)
   {
      // Render the solid queue
      ColorTextureLightShader_RenderQueue(shader, &shader->queue_solid);
   }
   else if(pass == e_SP_Transparent)
   {
      // Render the transparent queue
      ColorTextureLightShader_RenderQueue(shader, &shader->queue_transparent);
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

   RenderQueue_Init(&shader->queue_solid, sizeof(ColorTextureLightShaderState_T));
   RenderQueue_Init(&shader->queue_transparent, sizeof(ColorTextureLightShaderState_T));

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


void ColorTextureLightShader_InsertStateToQueue(ColorTextureLightShader_T * shader, int is_transparent)
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
