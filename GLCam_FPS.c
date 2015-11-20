#include <math.h>
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MatrixStack.h"
#include "GLCam_FPS.h"

#define TO_RAD(x) ((x) * 3.14f / 180.0f )

#define WALK_SPEED 5.0f
#define RUN_SPEED  10.0f
#define ROT_SPEED  0.004f
void GLCam_FPS_Init(GLCam_FPS_T * cam)
{
   int i;
   
   for(i = 0; i < e_fck_count; i ++)
   {
      cam->key_states[i] = 0;
   }
   cam->mouse_dx = 0;
   cam->mouse_dy = 0;
   
   
   Vector3D_Set(&cam->pos, 0, 0, 0);
   cam->yaw   = 0;
   cam->pitch = 0;
}


void GLCam_FPS_Update(GLCam_FPS_T * cam, float seconds)
{
   float rad_yaw, rad_pitch, sin_yaw, cos_yaw, sin_pitch, cos_pitch;
   Vector3D_T nv_forward, nv_right;
   float move_dist;
   
   rad_yaw   = cam->yaw;
   rad_pitch = cam->pitch;
   sin_yaw   = (float)sin(rad_yaw);
   cos_yaw   = (float)cos(rad_yaw);
   sin_pitch = (float)sin(rad_pitch);
   cos_pitch = (float)cos(rad_pitch);
   
   
   nv_forward.x = sin_yaw;
   nv_forward.y = -sin_pitch;
   nv_forward.z = -cos_yaw;
   
   nv_right.x = cos_yaw;
   nv_right.y = 0;
   nv_right.z = sin_yaw;
   
   if(cam->key_states[e_fck_run] == 1)
   {
      move_dist = RUN_SPEED * seconds;
   }
   else
   {
      move_dist = WALK_SPEED * seconds;
   }
   
   if(cam->key_states[e_fck_forward] == 1)
   {
      cam->pos.x -= nv_forward.x * move_dist;
      cam->pos.y -= nv_forward.y * move_dist;
      cam->pos.z -= nv_forward.z * move_dist;
   }
   else if(cam->key_states[e_fck_backward] == 1)
   {
      cam->pos.x += nv_forward.x * move_dist;
      cam->pos.y += nv_forward.y * move_dist;
      cam->pos.z += nv_forward.z * move_dist;
   }
   
   if(cam->key_states[e_fck_right] == 1)
   {
      cam->pos.x += nv_right.x * move_dist;
      cam->pos.y += nv_right.y * move_dist;
      cam->pos.z += nv_right.z * move_dist;
   }
   else if(cam->key_states[e_fck_left] == 1)
   {
      cam->pos.x -= nv_right.x * move_dist;
      cam->pos.y -= nv_right.y * move_dist;
      cam->pos.z -= nv_right.z * move_dist;
   }
   
   cam->yaw    -= ROT_SPEED * cam->mouse_dx;
   cam->pitch  -= ROT_SPEED * cam->mouse_dy;

   //printf("Z: %f\n", cam->pos.z);

   cam->mouse_dx = 0;
   cam->mouse_dy = 0;
}

void GLCam_FPS_Render(GLCam_FPS_T * cam, MatrixStack_T * stack)
{
   MatrixStack_ApplyXRotation(stack, cam->pitch);
   MatrixStack_ApplyYRotation(stack, cam->yaw);
   MatrixStack_ApplyTranslation(stack, -cam->pos.x, -cam->pos.y, -cam->pos.z);
}

void GLCam_FPS_Keyboard(GLCam_FPS_T * cam, GLCam_FPS_Key_T key, int state)
{
   cam->key_states[key] = state;
}

void GLCam_FPS_Mouse(GLCam_FPS_T * cam, int delta_x, int delta_y)
{
   cam->mouse_dx = delta_x;
   cam->mouse_dy = delta_y;
}


