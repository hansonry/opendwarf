#include "WavefrontMesh.h"

#include <stdlib.h>
#include <string.h>
#include "Resources.h"
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
   WMMeshTexture_T * mesh_texture, ** mt_list;
   size_t i, count;
   
   mesh_texture = NULL;
   mt_list = ObjectList_Get(obj_list, &count);
   for(i = 0; i < count; i++)
   {
      if(mt_list[i]->material_index == material_index)
      {
         mesh_texture = mt_list[i];
         break;
      }
   }


   return mesh_texture;
}

static void WavefrontMesh_Convert(WavefrontMesh_T * wmesh, WavefrontLoaderData_T * obj_data, const char * image_file_prefix)
{
   size_t i;
   size_t material_index;
   char * filename;
   const unsigned int mesh_sizes[3] = {3, 3, 2};
   float vertex[8];
   ManagerGLTexture2D_T * text_manager;
   WMMeshTexture_T * mesh_texture;
   
   text_manager = Resources_GetTextureManager();

   
   for(i = 0; i < obj_data->face_list_count; i++)
   {
      material_index = obj_data->face_list[i].material_index;
      mesh_texture = WavefrontMesh_LookupWMMeshTexture(&wmesh->mesh_texture_list, material_index);
      if(mesh_texture == NULL)
      {
         mesh_texture = malloc(sizeof(WMMeshTexture_T));
         ObjectList_Add(&wmesh->mesh_texture_list, mesh_texture);
         GLMeshBuilder_Init(&mesh_texture->mesh_builder, mesh_sizes, 3);
         mesh_texture->material_index = material_index;
         filename = FileTools_Append(image_file_prefix, obj_data->string_list[obj_data->material_list[material_index].mapKd_string_index]);
         mesh_texture->texture = ManagerGLTexture2D_Get(text_manager, filename);
         free(filename);
         

      }

      // Add Vertex

   }





   // One Mesh for each material


}

void WavefrontMesh_Init(WavefrontMesh_T * wmesh, WavefrontLoaderData_T * obj_data, const char * image_file_prefix)
{
   ObjectList_Init(&wmesh->mesh_texture_list);
   WavefrontMesh_Convert(wmesh, obj_data, image_file_prefix);
}

void WavefrontMesh_Destroy(WavefrontMesh_T * wmesh)
{
   size_t i, count;
   WMMeshTexture_T ** list;

   list = ObjectList_Get(&wmesh->mesh_texture_list, &count);
   
   for(i = 0; i < count; i++)
   {
      GLMesh_Cleanup(&list[i]->mesh);
      free(list[i]);
   }

   ObjectList_Destory(&wmesh->mesh_texture_list);

}

void WavefrontMesh_Render(WavefrontMesh_T * wmesh)
{
}

