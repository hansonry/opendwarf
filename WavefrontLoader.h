#ifndef __WAVEFRONTLOADER_H__
#define __WAVEFRONTLOADER_H__

typedef struct WavefrontLoaderData_S       WavefrontLoaderData_T;
typedef struct WavefrontLoaderVertex_S     WavefrontLoaderVertex_T;
typedef struct WavefrontLoaderNormal_S     WavefrontLoaderNormal_T;
typedef struct WavefrontLoaderUV_S         WavefrontLoaderUV_T;
typedef struct WavefrontLoaderFaceVertex_S WavefrontLoaderFaceVertex_T;
typedef struct WavefrontLoaderFace_S       WavefrontLoaderFace_T;

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
   size_t face_vertex_start_index;
   size_t face_vertex_count;

};


struct WavefrontLoaderData_S
{
   WavefrontLoaderVertex_T     * vertex_list;
   size_t                        vertex_list_count;
   WavefrontLoaderNormal_T     * normal_list;
   size_t                        normal_list_count;
   WavefrontLoaderUV_T         * uv_list;
   size_t                        uv_list_count;
   WavefrontLoaderFaceVertex_T * face_vertex_list;
   size_t                        face_vertex_count;
   WavefrontLoaderFace_T       * face_list;
   size_t                        face_list_count;
};


void WavefrontLoader_Load(WavefrontLoaderData_T * data, const char * filename, const char * material_path);


void WavefrontLoader_Delete(WavefrontLoaderData_T * data);


#endif // __WAVEFRONTLOADER_H__

