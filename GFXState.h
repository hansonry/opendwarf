#ifndef __GFXSTATE_H__
#define __GFXSTATE_H__

#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"

#include "Matrix3D.h"
#include "Shader.h"

typedef struct GFXState_S GFXState_T;
typedef struct GFXStateLight_S GFXStateLight_T;

struct GFXStateLight_S
{
   float pos_x;
   float pos_y;
   float pos_z;
   float color_r;
   float color_b;
   float color_g;
};


struct GFXState_S
{
   Shader_T        * shader;
   Matrix3D_T        world;
   Matrix3D_T        camera;
   Matrix3D_T        perspective;
   GFXStateLight_T   light_sun1;
};


void GFXState_Init(GFXState_T * state);
void GFXState_Destory(GFXState_T * state);


void GFXState_SetWorldMatrix(GFXState_T * state, const Matrix3D_T * world);
void GFXState_SetCameraMatrix(GFXState_T * state, const Matrix3D_T * camera);
void GFXState_SetPerspectiveMatrix(GFXState_T * state, const Matrix3D_T * perspective);

void GFXState_SetCameraMatrixToWorld(GFXState_T * state);

void GFXState_SetLightSun1DirectionAndColor(GFXState_T * state, float x, float y, float z, 
                                                                float r, float g, float b);


void GFXState_SetShader(GFXState_T * state, Shader_T * shader);

void GFXState_SetAllMatrixUniforms(GFXState_T * state, GLint world_matrix_uniform, 
                                                       GLint camera_world_matrix_uniform);

void GFXState_SetLightSun1Uniforms(GFXState_T * state, GLint light_location_uniform, 
                                                       GLint light_color_uniform);
#endif // __GFXSTATE_H__
