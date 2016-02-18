#include "WavefrontMesh.h"

#include <stdlib.h>
#include <string.h>
#include "RenderResources.h"
#include "GLMeshBuilder.h"
#include "FileTools.h"


typedef struct WMMeshTexture_S WMMeshTexture_T;
struct WMMeshTexture_S
{
   GLTexture2D_T * texture;
   GLMesh_T mesh;
   GLMeshBuilder_T mesh_builder;
   size_t material_index;
};



static WMMeshTexture_T * WavefrontMesh_LookupWMMeshTexture(ObjectList_T * obj_list, size_t material_index)
{
   WMMeshTexture_T * mesh_texture, * mt_item;
   size_t i, count;
   
   mesh_texture = NULL;
   count = ObjectList_Count(obj_list);
   for(i = 0; i < count; i++)
   {
      mt_item = ObjectList_Get(obj_list, i);
      if(mt_item->material_index == material_index)
      {
         mesh_texture = mt_item;
         break;
      }
   }


   return mesh_texture;
}

static void WavefrontMesh_Convert(WavefrontMesh_T * wmesh, WavefrontLoaderData_T * obj_data, const char * image_file_prefix)
{
   size_t i, k;
   size_t count;
   size_t vertex_count;
   size_t face_vertex_index;
   size_t material_index;
   char * filename;
   const unsigned int mesh_sizes[3] = {3, 3, 2};
   float vertex[8];
   ManagerGLTexture2D_T * text_manager;
   WMMeshTexture_T * mesh_texture, * mt_item;
   const WavefrontLoaderFaceVertex_T * vert;
   
   text_manager = Resources_GetTextureManager();

   vertex_count = 0;
   for(i = 0; i < obj_data->face_list_count; i++)
   {
      material_index = obj_data->face_list[i].material_index;
      mesh_texture = WavefrontMesh_LookupWMMeshTexture(&wmesh->mesh_texture_list, material_index);
      if(mesh_texture == NULL)
      {
         mesh_texture = malloc(sizeof(WMMeshTexture_T));
         ObjectList_AddAtEnd(&wmesh->mesh_texture_list, mesh_texture);
         GLMeshBuilder_Init(&mesh_texture->mesh_builder, mesh_sizes, 3);
         mesh_texture->material_index = material_index;
         filename = FileTools_Append(image_file_prefix, obj_data->string_list[obj_data->material_list[material_index].mapKd_string_index]);
         mesh_texture->texture = ManagerGLTexture2D_Get(text_manager, filename);
         free(filename);
         

      }

      // Add Face
      for(k = 2; k < 3; k --)
      {
         face_vertex_index = obj_data->face_list[i].face_vertex_start_index + k;
         vert = &obj_data->face_vertex_list[face_vertex_index];
         vertex[0] = obj_data->vertex_list[vert->vertex_index].x;
         vertex[1] = obj_data->vertex_list[vert->vertex_index].y;
         vertex[2] = obj_data->vertex_list[vert->vertex_index].z;
         vertex[3] = obj_data->normal_list[vert->normal_index].x;
         vertex[4] = obj_data->normal_list[vert->normal_index].y;
         vertex[5] = obj_data->normal_list[vert->normal_index].z;
         vertex[6] = obj_data->uv_list[vert->uv_index].u;
         vertex[7] = obj_data->uv_list[vert->uv_index].v;

         //printf("%i %i %i [%f, %f, %f, %f, %f, %f, %f, %f]\n", k,i, face_vertex_index, vertex[0], vertex[1], vertex[2], vertex[3], vertex[4], vertex[5], vertex[6], vertex[7]);

         GLMeshBuilder_Add1Vertex(&mesh_texture->mesh_builder, vertex);

         GLMeshBuilder_Add1Element(&mesh_texture->mesh_builder, vertex_count);
         vertex_count++;
         
         
      }

   }

   // One Mesh for each material
   count = ObjectList_Count(&wmesh->mesh_texture_list);
   for(i = 0; i < count; i ++)
   {
      mt_item = ObjectList_Get(&wmesh->mesh_texture_list, i);
      GLMeshBuilder_CreateGLMesh(&mt_item->mesh_builder, &mt_item->mesh);
      GLMesh_MoveToGFXCard(&mt_item->mesh);
      GLMeshBuilder_Destroy(&mt_item->mesh_builder);
   }


}

void WavefrontMesh_Init(WavefrontMesh_T * wmesh, WavefrontLoaderData_T * obj_data, const char * image_file_prefix)
{
   ObjectList_Init(&wmesh->mesh_texture_list, 0);
   WavefrontMesh_Convert(wmesh, obj_data, image_file_prefix);
}

void WavefrontMesh_Destroy(WavefrontMesh_T * wmesh)
{
   size_t i, count;
   WMMeshTexture_T * item;

   count = ObjectList_Count(&wmesh->mesh_texture_list);

   for(i = 0; i < count; i++)
   {
      item = ObjectList_Get(&wmesh->mesh_texture_list, i);
      GLMesh_Cleanup(&item->mesh);
      free(item);
   }

   ObjectList_Destory(&wmesh->mesh_texture_list);

}

void WavefrontMesh_Render(WavefrontMesh_T * wmesh, RenderQueue_T * render_queue, 
                                                   WavefrontShader_T * shader,
                                                   MemoryBlock_T * mem_block,
                                                   WavefrontShaderState_T * state_template, 
                                                   int is_transparent)
{
   WavefrontShaderState_T * state;
   WMMeshTexture_T * mt_item;
   size_t i, count;

   count = ObjectList_Count(&wmesh->mesh_texture_list);
   for(i = 0; i < count; i ++)
   {
      mt_item = ObjectList_Get(&wmesh->mesh_texture_list, i);
      state = MemoryBlock_Allocate(mem_block);
      memcpy(state, state_template, sizeof(WavefrontShaderState_T));

      WavefrontShaderState_SetMeshAndTexture(state, mt_item->texture, 
                                                    &mt_item->mesh, 
                                                    GL_TRIANGLES);
      RenderQueue_Add(render_queue, &shader->parent, state, is_transparent);
   }

}

