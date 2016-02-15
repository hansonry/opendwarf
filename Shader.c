#include "Shader.h"
#include "ShaderData.inc"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void Shader_Init(Shader_T * shader, const char               * shader_name, 
                                    ShaderType_T               type, 
                                    GLuint                     shader_id,
                                    Shader_Destoryer_Func_T    destroyer,
                                    Shader_RenderPass_Func_T   renderer)
{
   shader->name                 = shader_name;
   shader->type                 = type;
   shader->shader_id            = shader_id;
   shader->destroyer            = destroyer;
   shader->renderer             = renderer;
}

void Shader_Free(Shader_T * shader)
{
   if(shader->destroyer != NULL)
   {
      shader->destroyer(shader);
   }

   glDeleteProgram(shader->shader_id);   
   free(shader);
}

GLint Shader_GetUniform(Shader_T * shader, const char * uniform_name)
{
   GLint value;

   value = glGetUniformLocation(shader->shader_id, uniform_name);
   if(value == -1)
   {
      printf("Error: Shader_GetUniform: Couldn't find uniform: %s for shader %s\n", uniform_name, shader->name);
   }
   return value;
}


void Shader_Render(Shader_T * shader, void     * shader_data, 
                                      Shader_T * prev_shader, 
                                      Shader_T * next_shader)
{
   if((shader != NULL) && (shader->renderer != NULL) && (shader_data != NULL))
   {      
      shader->renderer(shader, shader_data, prev_shader, next_shader);
   }
}


