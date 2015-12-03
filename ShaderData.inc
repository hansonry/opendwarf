
typedef struct ShaderData_S ShaderData_T;
struct ShaderData_S
{
   const char * shader_id;
   const char * vertex_filename;
   const char * geometry_filename;
   const char * fragment_filename;
   int          max_locations;
   const char * uniform_names[e_SU_Last];
   
};


static const ShaderData_T SHADER_DATA_TABLE[] = 
{
//   Shader_Name  Vertex_Shader          Geometry_Shader  Fragment_Shader        Locations  World_Matrix   Perspective_World_Matrix  Light_Direction   Texture0
   { "test1",     "test1.vert.glsl",     NULL,            "test1.frag.glsl",     3,        {"WMatrix",     "PMatrix",                "LightDirection", "CSampler" }},
   { "block",     "block.vert.glsl",     NULL,            "block.frag.glsl",     3,        {"WMatrix",     "PMatrix",                "LightDirection", "CSampler" }},
   { "wavefront", "wavefront.vert.glsl", NULL,            "wavefront.frag.glsl", 3,        {"WMatrix",     "PMatrix",                "LightDirection", "CSampler" }},
   { NULL,        NULL,                  NULL,            NULL,                  0,        {NULL,          NULL,                     NULL,             NULL       }}
};

