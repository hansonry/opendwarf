#include "MapShader.h"
#include <stdlib.h>
#define UL(x) Shader_GetUniform(&shader->parent, (x))


static void MapShader_Destory(Shader_T * _shader)
{
   MapShader_T * shader = (MapShader_T*)_shader;
}

static void MapShader_Renderer(Shader_T * _shader, void     * _shader_data,
                                                   Shader_T * prev_shader,
                                                   Shader_T * next_shader)
{
   MapShader_T * shader = (MapShader_T *)_shader_data;
   MapShaderState_T * state = (MapShaderState_T *) _shader_data;
   if(_shader != prev_shader)
   {
      glUseProgram(shader->parent.shader_id);
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glActiveTexture(GL_TEXTURE0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

   if(_shader != next_shader)
   {
      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
   }
}


Shader_T * MapShader_Create(const char * shader_name, GLuint shader_id)
{
   MapShader_T * shader;
   shader = malloc(sizeof(MapShader_T));
   Shader_Init(&shader->parent, shader_name, 
                                e_ST_Map, 
                                shader_id,
                                MapShader_Destory,
                                MapShader_Renderer);

   shader->uniform_world             = UL("WMatrix");
   shader->uniform_world_perspective = UL("PMatrix");
   shader->uniform_texture           = UL("CSampler");
   shader->uniform_light_direction   = UL("LightDirection");
   shader->uniform_light_color       = -1; //UL("LightColor");


   return (Shader_T *)shader;
}



void MapShader_SetState(MapShader_T * shader, GFXState_T * state)
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

void MapShader_SetMeshAndTexture(MapShader_T * shader, GLTexture2D_T * texture, 
                                                       GLMesh_T * mesh, 
                                                       GLenum mesh_mode)
{
   shader->state.texture = texture;
   shader->state.mesh_mode = mesh_mode;
   shader->state.mesh = mesh;
}


MapShaderState_T * MapShader_CreateState(MapShader_T * shader)
{
}



