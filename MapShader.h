#ifndef __MAPSHADER_H__
#define __MAPSHADER_H__
#include "Shader.h"
#include "GFXState.h"
#include "GLTexture2D.h"
#include "GLMesh.h"

typedef struct MapShader_S       MapShader_T;
typedef struct MapShaderState_S  MapShaderState_T;

struct MapShaderState_S
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

struct MapShader_S
{
   Shader_T parent;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
};

Shader_T * MapShader_Create(const char * shader_name, GLuint shader_id);


void MapShaderState_SetGFXState(MapShaderState_T * state, GFXState_T * gfx_state);

void MapShaderState_SetMeshAndTexture(MapShaderState_T * state, GLTexture2D_T * texture, 
                                                         GLMesh_T * mesh, 
                                                         GLenum mesh_mode);





#endif // __MAPSHADER_H__

