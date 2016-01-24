#ifndef __GFXSTATE_H__
#define __GFXSTATE_H__
#include "Shader.h"
#include "GLTexture2D.h"

typedef struct GFXState_S GFXState_T;
struct GFXState_S
{
   Shader_T * shader;
   GLTexture2D_T * texture;
};


void GFXState_Init(GFXState_T * state);
void GFXState_Destory(GFXState_T * state);

void GFXState_SetShader(GFXState_T * state, Shader_T * shader);
void GFXState_SetTexture(GFXState_T * state, GLTexture2D_T * text, GLenum unit);

#endif // __GFXSTATE_H__
