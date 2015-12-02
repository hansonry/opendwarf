#ifndef __GLCAM_FPS_H__
#define __GLCAM_FPS_H__

#include "MatrixStack.h"

typedef enum GLCam_FPS_Key_E GLCam_FPS_Key_T;
typedef struct GLCam_FPS_S GLCam_FPS_T;

enum GLCam_FPS_Key_E
{
   e_fck_forward,
   e_fck_backward,
   e_fck_left,
   e_fck_right,
   e_fck_run,
   e_fck_count
};

struct GLCam_FPS_S
{
   Vector3D_T pos;
   float yaw;
   float pitch;
   int key_states[e_fck_count];
   int mouse_dx;
   int mouse_dy;
};




void GLCam_FPS_Init(GLCam_FPS_T * cam);


void GLCam_FPS_Update(GLCam_FPS_T * cam, float seconds);

void GLCam_FPS_Render(GLCam_FPS_T * cam, MatrixStack_T * stack);

void GLCam_FPS_Keyboard(GLCam_FPS_T * cam, GLCam_FPS_Key_T key, int state);
void GLCam_FPS_Mouse(GLCam_FPS_T * cam, int delta_x, int delta_y);



#endif // __GLCAM_FPS_H__

