#ifndef __SHADER_H__
#define __SHADER_H__

#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"

typedef struct Shader_S     Shader_T;
typedef enum   ShaderType_E ShaderType_T;

typedef Shader_T * (*Shader_Creater_Func_T)(const char * shader_name, GLuint shader_id);

enum ShaderType_E
{
   e_ST_ColorTextureLight,
   e_ST_Wavefront,
   e_ST_Last
};

struct Shader_S
{
   GLuint         shader_id;
   ShaderType_T   type;
   const char   * name;
   const int    * attribute_list;
   int            attribute_list_count;
};

Shader_T * Shader_Create(const char * shader_name);
void Shader_Init(Shader_T * shader, const char   * shader_name, 
                                    ShaderType_T   type, 
                                    GLuint         shader_id,
                                    const int    * attribute_list,
                                    int            attribute_list_count);
void Shader_Free(Shader_T * shader);

GLint Shader_GetUniform(Shader_T * shader, const char * uniform_name);



void Shader_Begin(Shader_T * shader);
void Shader_End(Shader_T * shader);

#endif // __SHADER_H__

