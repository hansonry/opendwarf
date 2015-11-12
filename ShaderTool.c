#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "ShaderTool.h"

typedef struct ShaderTool_SInfo_S ShaderTool_SInfo_T;
struct ShaderTool_SInfo_S
{
   const char * filename;
   char * source;
   long source_size;
   GLuint shader;
   GLenum shader_type;
   int compiled_flag;
   int attached_flag;

};

static void ShaderTool_LoadFile(ShaderTool_SInfo_T * info);
static void ShaderTool_CreateShader(ShaderTool_SInfo_T * info);
static void ShaderTool_CreateAndAttachShader(ShaderTool_SInfo_T * info, GLuint prog);

static void ShaderTool_PostLinkCleanup(ShaderTool_SInfo_T * info, GLuint prog);

GLuint ShaderTool_CreateShaderProgram(const char * vertex_shader_filename,
                                      const char * geometry_shader_filename,
                                      const char * fragment_shader_filename)
{
   GLuint prog;
   ShaderTool_SInfo_T vertex, geometry, fragment;
   char info_log[1024];
   GLint success;

   vertex.filename      = vertex_shader_filename;
   vertex.shader_type   = GL_VERTEX_SHADER;
   geometry.filename    = geometry_shader_filename;
   geometry.shader_type = GL_GEOMETRY_SHADER;
   fragment.filename    = fragment_shader_filename;
   fragment.shader_type = GL_FRAGMENT_SHADER;

   prog = glCreateProgram();

   ShaderTool_CreateAndAttachShader(&vertex,   prog);
   ShaderTool_CreateAndAttachShader(&geometry, prog);
   ShaderTool_CreateAndAttachShader(&fragment, prog);

   glLinkProgram(prog);

   glGetProgramiv(prog, GL_LINK_STATUS, &success);
   if(success)
   {
      glValidateProgram(prog);
   }
   else
   {
      glGetProgramInfoLog(prog, sizeof(info_log), NULL, info_log);
      printf("Error: ShaderTool_CreateShaderProgram Failed to link program containg:\n");
      if(vertex.attached_flag)
      {
         printf("Error: File: %s\n", vertex.filename);
      }
      if(geometry.attached_flag)
      {
         printf("Error: File: %s\n", geometry.filename);
      }
      if(fragment.attached_flag)
      {
         printf("Error: File: %s\n", fragment.filename);
      }
      printf("Program Error: %s\n", info_log);
   }

   ShaderTool_PostLinkCleanup(&vertex,   prog);
   ShaderTool_PostLinkCleanup(&geometry, prog);
   ShaderTool_PostLinkCleanup(&fragment, prog);


   return prog;
}


static void ShaderTool_LoadFile(ShaderTool_SInfo_T * info)
{
   FILE *fp;
   size_t fsize;
   char * buffer;
   size_t read;

   info->source = NULL;
   info->source_size = 0;


   fp = fopen(info->filename, "rb");
   if(fp != NULL)
   {
      fseek(fp, 0L, SEEK_END);
      fsize = ftell(fp);
      rewind(fp);

      buffer = calloc(sizeof(char), fsize);
      read = fread(buffer, sizeof(char), fsize, fp); 
      if(read == fsize)
      {
         info->source_size = fsize;
         info->source = buffer;
      }
      else
      {
         printf("Error: ShaderTool_LoadFile: Can't Load Data from File %s\n", info->filename);
         free(buffer);
      }
      fclose(fp);
   }
   else     
   {
      printf("Error: ShaderTool_LoadFile: Can't Open File %s\n", info->filename);
   }
}


static void ShaderTool_CreateAndAttachShader(ShaderTool_SInfo_T * info, GLuint prog)
{
   info->attached_flag = 0;
   info->compiled_flag = 0;
   info->source = NULL;
   if(info->filename != NULL)
   {
      ShaderTool_LoadFile(info);
      if(info->source != NULL)
      {
         ShaderTool_CreateShader(info);
         if(info->compiled_flag == 1)
         {
            glAttachShader(prog, info->shader);
            info->attached_flag = 1;
         }
      }
   }
}

static void ShaderTool_CreateShader(ShaderTool_SInfo_T * info)
{
   const GLchar * source_array[1];
   GLint length_array[1];
   GLint success;
   GLchar info_log[1024];


   source_array[0] = info->source;
   length_array[0] = info->source_size;

   info->shader = glCreateShader(info->shader_type);

   glShaderSource(info->shader, 1, source_array, length_array);
   glCompileShader(info->shader);

   glGetShaderiv(info->shader, GL_COMPILE_STATUS, &success);
   if(success)
   {
      info->compiled_flag = 1;
   }
   else
   {
      glGetShaderInfoLog(info->shader, sizeof(info_log), NULL, info_log);
      printf("Error: ShaderTool_CreateShader Failed to compile the %d shader %s\n", info->shader_type, info->filename);
      printf("Shader Error: %s\n", info_log);
      info->compiled_flag = 0;
      glDeleteShader(info->shader);
   }

}

static void ShaderTool_PostLinkCleanup(ShaderTool_SInfo_T * info, GLuint prog)
{
   if(info->attached_flag)
   {
      glDetachShader(prog, info->shader);
      glDeleteShader(info->shader);
      info->shader = 0;
   }

   if(info->source != NULL)
   {
      free(info->source);
      info->source = NULL;
   }
}

