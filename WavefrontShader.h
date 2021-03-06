#ifndef __WAVEFRONTSHADER_H__
#define __WAVEFRONTSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"
#include "GLMesh.h"


typedef struct WavefrontShader_S       WavefrontShader_T;
typedef struct WavefrontShaderState_S  WavefrontShaderState_T;

struct WavefrontShaderState_S
{
   Matrix3D_T matix_world;
   Matrix3D_T matix_world_perspective;
   GLTexture2D_T * texture;
   float light_color_r;
   float light_color_b;
   float light_color_g;
   float light_direction_x;
   float light_direction_y;
   float light_direction_z;
   GLMesh_T * mesh;
   GLenum mesh_mode;
};

struct WavefrontShader_S
{
   Shader_T parent;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
};

Shader_T * WavefrontShader_Create(const char * shader_name, GLuint shader_id);


void WavefrontShaderState_SetGFXState(WavefrontShaderState_T * state, GFXState_T * gfx_state);
void WavefrontShaderState_SetMeshAndTexture(WavefrontShaderState_T * state, GLTexture2D_T * texture, 
                                                                            GLMesh_T * mesh, 
                                                                            GLenum mesh_mode);




#endif // __WAVEFRONTSHADER_H__

