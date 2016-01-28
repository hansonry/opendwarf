#include "Shader.h"
#include "ShaderData.inc"

#include <stdio.h>
#include <string.h>

static Shader_T * last_active_shader = NULL;

static const ShaderData_T * Shader_LookupData(const char * shader_name)
{
   const ShaderData_T * out;
   int i;

   out = NULL;
   i = 0;
   while(SHADER_DATA_TABLE[i].shader_id != NULL && out == NULL)
   {
      if(strcmp(SHADER_DATA_TABLE[i].shader_id, shader_name) == 0)
      {
         out = &SHADER_DATA_TABLE[i];
      }
      i++;
   }


   return out;
}

void Shader_Load(Shader_T * shader, const char * shader_name)
{
   const ShaderData_T * data;
   int i;
   data = Shader_LookupData(shader_name);

   if(data == NULL)
   {
      printf("Error: Shader_Load could not find shader name: %s\n", shader_name);
   }
   else
   {

      shader->shader_id = ShaderTool_CreateShaderProgram(data->vertex_filename, 
                                                         data->geometry_filename, 
                                                         data->fragment_filename);
      ShaderInterface_Init(&shader->shaderi, data->type, shader->shader_id);
   }
}

void Shader_Free(Shader_T * shader)
{
   ShaderInterface_Destory(&shader->shaderi);
   glDeleteProgram(shader->shader_id);
}

void Shader_SetTexutre(Shader_T * shader, const char * uniform, 
                                          GLTexture2D_T * texture, 
                                          GLenum slot)
{
   GLTexture2D_ApplyToUniform(texture, uniform, slot);
}

void Shader_SetPositionPerspective(Shader_T * shader, const char * uniform_world, 
                                                      const char * uniform_perspective_world, 
                                                      const Matrix3D_T * world, 
                                                      const Matrix3D_T * perspective)
{
   Matrix3D_T temp;
   Matrix3D_Multiply(&temp, perspective, world);

   glUniformMatrix4fv(uniform_world,             1, GL_FALSE, world->data);
   glUniformMatrix4fv(uniform_perspective_world, 1, GL_FALSE, temp.data);
}

void Shader_SetLightDirection(Shader_T * shader, const char * uniform, 
                                                 float lx, float ly, float lz)
{
   glUniform3f(uniform, lx, ly, lz);
}

void Shader_Begin(Shader_T * shader)
{
   glUseProgram(shader->shader_id);
}

void Shader_VertexAttributesEnable(int count)
{
   int i;
   for(i = 0; i < count; i++)
   {
      glEnableVertexAttribArray(i);
   }
}

void Shader_VertexAttributesDissable(int count)
{
   int i;
   for(i = 0; i < count; i++)
   {
      glDisableVertexAttribArray(i);
   }
}



void Shader_Use(Shader_T * shader)
{
   if(last_active_shader != shader)
   {
      if(shader == NULL)
      {
         glUseProgram(0);
      }
      else
      {
         glUseProgram(shader->shader_id);
      }
      last_active_shader = shader;
   }
}


void Shader_UpdateUniforms(Shader_T * shader, GFXState_T * gfx_state)
{
   ShaderInterface_Setup(&shader->shaderi, gfx_state);
}



