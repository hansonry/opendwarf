#ifndef __WAVEFRONTLOADER_H__
#define __WAVEFRONTLOADER_H__

typedef struct WavefrontLoaderData_S         WavefrontLoaderData_T;
typedef struct WavefrontLoaderVertex_S       WavefrontLoaderVertex_T;
typedef struct WavefrontLoaderNormal_S       WavefrontLoaderNormal_T;
typedef struct WavefrontLoaderUV_S           WavefrontLoaderUV_T;
typedef struct WavefrontLoaderFaceVertex_S   WavefrontLoaderFaceVertex_T;
typedef struct WavefrontLoaderFace_S         WavefrontLoaderFace_T;
typedef struct WavefrontLoaderMaterialLib_S  WavefrontLoaderMaterialLib_T;
typedef struct WavefrontLoaderMaterial_S     WavefrontLoaderMaterial_T;


struct WavefrontLoaderMaterial_S
{
   size_t name_string_index;
   size_t mapKd_string_index;
};

struct WavefrontLoaderMaterialLib_S
{
   size_t filename_string_index;
};

struct WavefrontLoaderUV_S
{
   float u;
   float v;
   float w; // Default to 0.0f
};

struct WavefrontLoaderVertex_S
{
   float x;
   float y;
   float z;
   float w; // Default to 1.0f
};

struct WavefrontLoaderNormal_S
{
   float x;
   float y;
   float z;
};

struct WavefrontLoaderFaceVertex_S
{
   size_t vertex_index;
   size_t normal_index;
   size_t uv_index;
};

struct WavefrontLoaderFace_S
{
   size_t material_index;
   size_t material_string_index;
   size_t face_vertex_start_index;
   size_t face_vertex_count;
};


struct WavefrontLoaderData_S
{
   WavefrontLoaderVertex_T      *  vertex_list;
   size_t                          vertex_list_count;
   size_t                          vertex_list_size;
   WavefrontLoaderNormal_T      *  normal_list;
   size_t                          normal_list_count;
   size_t                          normal_list_size;
   WavefrontLoaderUV_T          *  uv_list;
   size_t                          uv_list_count;
   size_t                          uv_list_size;
   WavefrontLoaderFaceVertex_T  *  face_vertex_list;
   size_t                          face_vertex_list_count;
   size_t                          face_vertex_list_size;
   WavefrontLoaderFace_T        *  face_list;
   size_t                          face_list_count;
   size_t                          face_list_size;
   char                         ** string_list;
   size_t                          string_list_count;
   size_t                          string_list_size;
   WavefrontLoaderMaterialLib_T *  materiallib_list;
   size_t                          materiallib_list_count;
   size_t                          materiallib_list_size;
   WavefrontLoaderMaterial_T    *  material_list;
   size_t                          material_list_count;
   size_t                          material_list_size;
};

// Load the obj data file
void WavefrontLoader_Load(WavefrontLoaderData_T * data, const char * filename);

// Load all the mtl files refreced in obj file
void WavefrontLoader_LoadMaterialLibs(WavefrontLoaderData_T * data, const char * material_prefix_path);

// Refrences face material index to actual materials
void WavefrontLoader_LookupMaterial(WavefrontLoaderData_T * data);

// cleanup
void WavefrontLoader_Delete(WavefrontLoaderData_T * data);


#endif // __WAVEFRONTLOADER_H__

