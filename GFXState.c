#include "GFXState.h"

void GFXState_Init(GFXState_T * state)
{
   state->shader = NULL;
   state->texture = NULL;
}
void GFXState_Destory(GFXState_T * state)
{
   if(state->shader != NULL)
   {
      Shader_End(state->shader);
   }
}

void GFXState_SetShader(GFXState_T * state, Shader_T * shader)
{

   if(state->shader != shader)
   {
      if(state->shader != NULL)
      {
         Shader_End(state->shader);
      }
      state->shader = shader;
      Shader_Begin(state->shader);

   }

}
void GFXState_SetTexture(GFXState_T * state, GLTexture2D_T * text, GLenum unit);
{
   GLTexture2D_BindToUnit(text, unit);
}
