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

Shader_T * Shader_Create(const char * shader_name)
{
   const ShaderData_T * data;
   Shader_T * shader;
   GLuint shader_id;
   data = Shader_LookupData(shader_name);

   if(data == NULL)
   {
      printf("Error: Shader_Load: Could not find shader name: %s\n", shader_name);
      shader = NULL;
   }
   else
   {

      shader_id = ShaderTool_CreateShaderProgram(data->vertex_filename, 
                                                 data->geometry_filename, 
                                                 data->fragment_filename);
      shader = data->create_function(data->shader_id, shader_id);
   }
   return shader;
}

void Shader_Init(Shader_T * shader, const char * shader_name, ShaderType_T type, GLuint shader_id)
{
   shader->name = shader_name;
   shader->type = type;
   shader->shader_id = shader_id;
}

void Shader_Free(Shader_T * shader)
{
   glDeleteProgram(shader->shader_id);
   free(shader);
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

GLint Shader_GetUniform(Shader_T * shader, const char * uniform_name)
{
   GLint value;

   value = glGetUniformLocation(shader->shader_id, uniform_name);
   if(value == -1)
   {
      printf("Error: Shader_GetUniform: Couldn't find uniform: %s\n", uniform_name);
   }
   return value;
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





