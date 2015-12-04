#ifndef __SHADER_H__
#define __SHADER_H__

#include "GLTexture2D.h"
#include "Matrix3D.h"

typedef enum   ShaderUniforms_E ShaderUniforms_T;
typedef struct Shader_S         Shader_T;

enum ShaderUniforms_E
{
   e_SU_Mat4_World,
   e_SU_Mat4_Perspective_World,
   e_SU_Vec3_Light_Direction,
   e_SU_Samp2D_Texture0,
   e_SU_Last
};

struct Shader_S
{
   GLuint shader_id;
   GLint  uniforms[e_SU_Last];
   int    max_location;
};

void Shader_Load(Shader_T * shader, const char * shader_name);
void Shader_Free(Shader_T * shader);

void Shader_SetTexutre(Shader_T * shader, GLTexture2D_T * texture, GLenum slot);
void Shader_SetPositionPerspective(Shader_T * shader, const Matrix3D_T * position, const Matrix3D_T * perspective);
void Shader_SetLightDirection(Shader_T * shader, float lx, float ly, float lz);

void Shader_Begin(Shader_T * shader);
void Shader_End(Shader_T * shader);






#endif // __SHADER_H__

