#ifndef __SHADER_H__
#define __SHADER_H__

typedef struct GFXState_S GFXState_T;

#include "GLTexture2D.h"
#include "Matrix3D.h"
#include "ShaderInterface.h"

typedef struct Shader_S Shader_T;

struct Shader_S
{
   GLuint shader_id;
   ShaderInterface_T shaderi;
};

void Shader_Load(Shader_T * shader, const char * shader_name);
void Shader_Free(Shader_T * shader);


void Shader_Use(Shader_T * shader);
void Shader_UpdateUniforms(Shader_T * shader, GFXState_T * gfx_state);

#endif // __SHADER_H__

