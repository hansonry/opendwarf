#ifndef __COLORTEXTURELIGHTSHADER_H__
#define __COLORTEXTURELIGHTSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"
#include "RenderQueue.h"
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
   RenderQueue_T queue_solid;
   RenderQueue_T queue_transparent;
   ColorTextureLightShaderState_T state;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
   GLint uniform_color;
};

Shader_T * ColorTextureLightShader_Create(const char * shader_name, GLuint shader_id);


void ColorTextureLightShader_SetState(ColorTextureLightShader_T * shader, GFXState_T * state);

void ColorTextureLightShader_SetColor(ColorTextureLightShader_T * shader, float color_r,
                                                                          float color_g,
                                                                          float color_b,
                                                                          float color_a);

void ColorTextureLightShader_SetMeshAndTexture(ColorTextureLightShader_T * shader, GLTexture2D_T * texture, 
                                                                                   GLMesh_T * mesh, 
                                                                                   GLenum mesh_mode);

void ColorTextureLightShader_InsertStateToQueue(ColorTextureLightShader_T * shader, int is_transparent);



#endif // __COLORTEXTURELIGHTSHADER_H__

