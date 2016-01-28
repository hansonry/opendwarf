#ifndef __SHADERINTERFACE_H__
#define __SHADERINTERFACE_H__

typedef struct ShaderInterface_S     ShaderInterface_T;
typedef enum   ShaderInterfaceType_E ShaderInterfaceType_T;

enum ShaderInterfaceType_E
{
   e_SIT_ColorTextureLight,
   e_SIT_Last
};

typedef struct SIColorTextureLight_S SIColorTextureLight_T;

struct SIColorTextureLight_S
{
   GLint uniform_color;
   GLint uniform_texture;
   GLint uniform_world;
   GLint uniform_world_perspective;
   GLint uniform_light_direction;
   GLint uniform_light_color;
};


struct ShaderInterface_S
{
   ShaderInterfaceType_T type;
   union
   {
      SIColorTextureLight_T color_texture_light;
   } data;
};


void ShaderInterface_Init(ShaderInterface_T * shaderi, ShaderInterfaceType_T type, 
                                                       GLuint shader_id);
void ShaderInterface_Destory(ShaderInterface_T * shaderi);

void ShaderInterface_Setup(ShaderInterface_T * shaderi, GLuint shader_id, GFXState_T * gfx_state);

#endif __SHADERINTERFACE_H__

