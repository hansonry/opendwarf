#ifndef __SHADER_H__
#define __SHADER_H__

#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"

typedef struct Shader_S     Shader_T;
typedef enum   ShaderType_E ShaderType_T;
typedef enum   ShaderPass_E ShaderPass_T;

typedef Shader_T * (*Shader_Creater_Func_T)(const char * shader_name, GLuint shader_id);
typedef void (*Shader_Destoryer_Func_T)(Shader_T * shader);
typedef void (*Shader_RenderPass_Func_T)(Shader_T * shader, ShaderPass_T pass);

enum ShaderPass_E
{
   e_SP_Solid,
   e_SP_Transparent,
   e_SP_Last
};

enum ShaderType_E
{
   e_ST_ColorTextureLight,
   e_ST_Wavefront,
   e_ST_Map,
   e_ST_Last
};

struct Shader_S
{
   GLuint                     shader_id;
   ShaderType_T               type;
   const char               * name;
   Shader_Destoryer_Func_T    destroyer;
   Shader_RenderPass_Func_T   renderer;
};

Shader_T * Shader_Create(const char * shader_name);
void Shader_Init(Shader_T * shader, const char               * shader_name, 
                                    ShaderType_T               type, 
                                    GLuint                     shader_id,
                                    Shader_Destoryer_Func_T    destroyer,
                                    Shader_RenderPass_Func_T   renderer);
void Shader_Free(Shader_T * shader);

GLint Shader_GetUniform(Shader_T * shader, const char * uniform_name);

void Shader_Render(Shader_T * shader, ShaderPass_T pass);




#endif // __SHADER_H__

