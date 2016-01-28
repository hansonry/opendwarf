#include <stdio.h>
#include "GFXState.h"
#include "ShaderInterface.h"

#define UL(x, y) glGetUniformLocation((x), (y))


typedef struct FuncList_S FuncList_T;

typedef void (*Shader_Init_T)(ShaderInterface_T * shaderi, GLuint shader_id);
typedef void (*Shader_Destory_T)(ShaderInterface_T * shaderi);
typedef void (*Shader_Setup_T)(ShaderInterface_T * shaderi, GFXState_T * gfx_state);

struct FuncList_S
{
   Shader_Init_T     init;
   Shader_Destory_T  destroy; 
   Shader_Setup_T    setup;
};

// == EmptyInterface == //
static void Shader_Empty_Init(ShaderInterface_T * shaderi, GLuint shader_id)
{
   shaderi   = shaderi;
   shader_id = shader_id;
}

static void Shader_Empty_Destory(ShaderInterface_T * shaderi)
{
   shaderi   = shaderi;
}

istatic void Shader_Empty_Setup(ShaderInterface_T * shaderi, GFXState_T * gfx_state)
{
   shaderi   = shaderi;
   gfx_state = gfx_state;
}

// == ColorTextureLightInterface == //
static void Shader_ColorTextureLight_Init(ShaderInterface_T * shaderi, GLuint shader_id)
{
   SIColorTextureLight_T * data;
   data = &shaderi->data.color_texture_light;

   data->uniform_world             = UL(shader_id, "WMatrix");
   data->uniform_world_perspective = UL(shader_id, "PMatrix");
   data->uniform_texture           = UL(shader_id, "CSampler");
   data->uniform_color             = UL(shader_id, "Color");
   data->uniform_light_direction   = UL(shader_id, "LightDirection");
   data->uniform_light_color       = UL(shader_id, "LightColor");
}


static void Shader_ColorTextureLight_Setup(ShaderInterface_T * shaderi, GFXState_T * gfx_state)
{
   GFXState_SetAllMatrixUniforms(gfx_state, data->uniform_world, 
                                            data->uniform_world_perspective);
   glUniform3f(data->uniform_light_direction, lx, ly, lz);
   glUniform3f(data->uniform_light_color, lx, ly, lz);
}


static const FuncList_T call_table[e_SIT_Last] = 
{
   /* e_SIT_ColorTextureLight */ { Shader_ColorTextureLight_Init, Shader_Empty_Destory, Shader_ColorTextureLight_Setup } 
};



void ShaderInterface_Init(ShaderInterface_T * shaderi, ShaderInterfaceType_T type, 
                                                       GLuint shader_id)
{
   if(type < e_SIT_Last)
   {
      shaderi->type = type;
      call_table[shaderi->type].init(shaderi, shader_id);
   }
   else
   {
      printf("Error: ShaderInterface_Init: type is not a valid shader type: %i\n", type);
   }
}

void ShaderInterface_Destory(ShaderInterface_T * shaderi)
{
   if(type < e_SIT_Last)
   {
      call_table[shaderi->type].destroy(shaderi);
   }
   else
   {
      printf("Error: ShaderInterface_Destory: type is not a valid shader type: %i\n", type);
   }
}

void ShaderInterface_Setup(ShaderInterface_T * shaderi, GLuint shader_id, GFXState_T * gfx_state)
{
   if(type < e_SIT_Last)
   {
      call_table[shaderi->type].setup(shaderi, shader_id, gfx_state);
   }
   else
   {
      printf("Error: ShaderInterface_Setup: type is not a valid shader type: %i\n", type);
   }
}

