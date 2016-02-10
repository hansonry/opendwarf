
#include "ColorTextureLightShader.h"
#include "WavefrontShader.h"
#include "MapShader.h"

typedef struct ShaderData_S ShaderData_T;
struct ShaderData_S
{
   const char            * shader_id;
   const char            * vertex_filename;
   const char            * geometry_filename;
   const char            * fragment_filename;
   Shader_Creater_Func_T   create_function;
};


static const ShaderData_T SHADER_DATA_TABLE[] = 
{
//   Shader_Name            Vertex_Shader                    Geometry_Shader  Fragment_Shader                  Create Function
   { "block",               "block.vert.glsl",               NULL,            "block.frag.glsl",               MapShader_Create },
   { "wavefront",           "wavefront.vert.glsl",           NULL,            "wavefront.frag.glsl",           WavefrontShader_Create },
   { "color_texture_light", "color_texture_light.vert.glsl", NULL,            "color_texture_light.frag.glsl", ColorTextureLightShader_Create },
   { NULL,                  NULL,                            NULL,            NULL,                            NULL                           }
};

