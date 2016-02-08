#include "WavefrontShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))

static const int attrib_data[] = {0, 1, 2};


static void WavefrontShader_Destory(Shader_T * _shader)
{
   WavefrontShader_T * shader = (WavefrontShader_T*)_shader;
   RenderQueue_Destory(&shader->queue_solid);
   RenderQueue_Destory(&shader->queue_transparent);
}

static void WavefrontShader_RenderQueue(WavefrontShader_T * shader, RenderQueue_T * queue)
{
   WavefrontShaderState_T state;
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
      glBindTexture(GL_TEXTURE_2D, state.texture->gl_id);
      GLMesh_Render(state.mesh, state.mesh_mode);
   }
   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}

static void WavefrontShader_Renderer(Shader_T * _shader, ShaderPass_T pass)
{
   WavefrontShader_T * shader = (WavefrontShader_T*)_shader;
   if(pass == e_SP_Solid)
   {
      // Render the solid queue
      WavefrontShader_RenderQueue(shader, &shader->queue_solid);
   }
   else if(pass == e_SP_Transparent)
   {
      // Render the transparent queue
      WavefrontShader_RenderQueue(shader, &shader->queue_transparent);
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

   RenderQueue_Init(&shader->queue_solid, sizeof(WavefrontShaderState_T));
   RenderQueue_Init(&shader->queue_transparent, sizeof(WavefrontShaderState_T));

   return (Shader_T *)shader;
}



void WavefrontShader_SetState(WavefrontShader_T * shader, GFXState_T * state)
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

void WavefrontShader_SetMeshAndTexture(WavefrontShader_T * shader, GLTexture2D_T * texture, 
                                                                   GLMesh_T * mesh, 
                                                                   GLenum mesh_mode)
{
   shader->state.texture = texture;
   shader->state.mesh_mode = mesh_mode;
   shader->state.mesh = mesh;
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


