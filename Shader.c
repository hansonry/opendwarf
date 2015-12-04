#include "Shader.h"
#include "ShaderData.inc"

#include <stdio.h>
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
      shader->max_location = data->max_locations;

      for(i = 0; i < e_SU_Last; i++)
      {
         if(data->uniform_names[i] == NULL)
         {
            shader->uniforms[i] = -1;
         }
         else
         {
            shader->uniforms[i] = glGetUniformLocation(shader->shader_id, 
                                                       data->uniform_names[i]);
            if(shader->uniforms[i] == -1)
            {
               printf("Error: Shader_Load using shader \"%s\" couldn't find uniform location for %s\n", shader_name,  data->uniform_names[i]);
            }
         }
      }
   }



}

void Shader_Free(Shader_T * shader)
{
   glDeleteProgram(shader->shader_id);
}

void Shader_SetTexutre(Shader_T * shader, GLTexture2D_T * texture, GLenum slot)
{
   GLTexture2D_ApplyToUniform(texture, shader->uniforms[e_SU_Samp2D_Texture0], slot);
}

void Shader_SetPositionPerspective(Shader_T * shader, const Matrix3D_T * world, const Matrix3D_T * perspective)
{
   Matrix3D_T temp;
   Matrix3D_Multiply(&temp, perspective, world);

   glUniformMatrix4fv(shader->uniforms[e_SU_Mat4_World],             1, GL_FALSE, world->data);
   glUniformMatrix4fv(shader->uniforms[e_SU_Mat4_Perspective_World], 1, GL_FALSE, temp.data);
}

void Shader_SetLightDirection(Shader_T * shader, float lx, float ly, float lz)
{
   glUniform3f(shader->uniforms[e_SU_Vec3_Light_Direction], lx, ly, lz);
}

void Shader_Begin(Shader_T * shader)
{
   int i;

   glUseProgram(shader->shader_id);
   for(i = 0; i < shader->max_location; i++)
   {
      glEnableVertexAttribArray(i);
   }
}

void Shader_End(Shader_T * shader)
{
   int i;

   for(i = 0; i < shader->max_location; i++)
   {
      glDisableVertexAttribArray(i);
   }
   glUseProgram(0);
}



