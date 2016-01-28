
typedef struct ShaderData_S ShaderData_T;
struct ShaderData_S
{
   const char            * shader_id;
   const char            * vertex_filename;
   const char            * geometry_filename;
   const char            * fragment_filename;
   ShaderInterfaceType_T   interface_type;
};


static const ShaderData_T SHADER_DATA_TABLE[] = 
{
//   Shader_Name            Vertex_Shader                    Geometry_Shader  Fragment_Shader                  Interface_Type
   { "test1",               "test1.vert.glsl",               NULL,            "test1.frag.glsl",               e_SIT_ColorTextureLight },
   { "block",               "block.vert.glsl",               NULL,            "block.frag.glsl",               e_SIT_ColorTextureLight },
   { "wavefront",           "wavefront.vert.glsl",           NULL,            "wavefront.frag.glsl",           e_SIT_ColorTextureLight },
   { "decal",               "decal.vert.glsl",               NULL,            "decal.frag.glsl",               e_SIT_ColorTextureLight },
   { "color_texture_light", "color_texture_light.vert.glsl", NULL,            "color_texture_light.frag.glsl", e_SIT_ColorTextureLight },
   { NULL,                  NULL,                            NULL,            NULL,                            e_SIT_Last              }
};

