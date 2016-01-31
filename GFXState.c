#include "GFXState.h"

#include <math.h>

void GFXState_Init(GFXState_T * state)
{
   Matrix3D_SetIdentity(&state->world);
   Matrix3D_SetIdentity(&state->camera);
   Matrix3D_SetIdentity(&state->perspective);
   state->shader = NULL;
}
void GFXState_Destory(GFXState_T * state)
{
}


void GFXState_SetWorldMatrix(GFXState_T * state, const Matrix3D_T * world)
{
   Matrix3D_Copy(&state->world, world);
}

void GFXState_SetCameraMatrix(GFXState_T * state, const Matrix3D_T * camera)
{
   Matrix3D_Copy(&state->camera, camera);
}

void GFXState_SetPerspectiveMatrix(GFXState_T * state, const Matrix3D_T * perspective)
{
   Matrix3D_Copy(&state->perspective, perspective);
}

void GFXState_SetCameraMatrixToWorld(GFXState_T * state)
{
   Matrix3D_Copy(&state->camera, &state->world);
}

static void Normalize(float * x, float * y, float * z)
{
   float dist2 = ((*x) * (*x)) + ((*y) * (*y)) + ((*z) * (*z));

   float dist = sqrt(dist2);
   if(dist > 0)
   {
      (*x) = (*x) / dist;
      (*y) = (*y) / dist;
      (*z) = (*z) / dist;
      
   }
}

void GFXState_SetLightSun1DirectionAndColor(GFXState_T * state, float x, float y, float z, 
                                                                float r, float g, float b)
{
   Normalize(&x, &y, &z);
   state->light_sun1.pos_x = x;
   state->light_sun1.pos_y = y;
   state->light_sun1.pos_z = z;

   state->light_sun1.color_r = r;
   state->light_sun1.color_g = g;
   state->light_sun1.color_b = b;
}

void GFXState_SetShader(GFXState_T * state, Shader_T * shader)
{
   if(state->shader != shader)
   {
      Shader_End(state->shader);
      state->shader = shader;
      Shader_Begin(state->shader);
   }
}


void GFXState_SetAllMatrixUniforms(GFXState_T * state, GLint world_matrix_uniform, 
                                                       GLint camera_world_matrix_uniform)
{
   Matrix3D_T world_camera;
   Matrix3D_T world_camera_perspective;

   Matrix3D_Multiply(&world_camera,             &state->camera,      &state->world);
   Matrix3D_Multiply(&world_camera_perspective, &state->perspective, &world_camera);

   glUniformMatrix4fv(world_matrix_uniform,        1, GL_FALSE, world_camera.data);
   glUniformMatrix4fv(camera_world_matrix_uniform, 1, GL_FALSE, world_camera_perspective.data);
}

void GFXState_SetLightSun1Uniforms(GFXState_T * state, GLint light_location_uniform,
                                                       GLint light_color_uniform)
{

   glUniform3f(light_location_uniform, state->light_sun1.pos_x, 
                                       state->light_sun1.pos_y,
                                       state->light_sun1.pos_z);
   glUniform3f(light_color_uniform, state->light_sun1.color_r, 
                                    state->light_sun1.color_g,
                                    state->light_sun1.color_b);
}

