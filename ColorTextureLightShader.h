#ifndef __COLORTEXTURELIGHTSHADER_H__
#define __COLORTEXTURELIGHTSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"
#include "GLMesh.h"

typedef struct ColorTextureLightShader_S       ColorTextureLightShader_T;
typedef struct ColorTextureLightShaderState_S  ColorTextureLightShaderState_T;

struct ColorTextureLightShaderState_S
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
   float color_r;
   float color_g;
   float color_b;
   float color_a;
   GLMesh_T * mesh;
   GLenum mesh_mode;
};

struct ColorTextureLightShader_S
{
   Shader_T parent;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
   GLint uniform_color;
};

Shader_T * ColorTextureLightShader_Create(const char * shader_name, GLuint shader_id);


void ColorTextureLightShaderState_SetGFXState(ColorTextureLightShaderState_T * state, GFXState_T * gfx_state);

void ColorTextureLightShaderState_SetColor(ColorTextureLightShaderState_T * state, float color_r,
                                                                                   float color_g,
                                                                                   float color_b,
                                                                                   float color_a);

void ColorTextureLightShaderState_SetMeshAndTexture(ColorTextureLightShaderState_T * state, GLTexture2D_T * texture, 
                                                                                            GLMesh_T * mesh, 
                                                                                            GLenum mesh_mode);




#endif // __COLORTEXTURELIGHTSHADER_H__

