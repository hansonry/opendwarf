#include "MapItemListRenderer.h"

#include "WavefrontLoader.h"
#include "Resources.h"


static void MapItemListRender_LoadResources(MapItemListRenderer_T * rend)
{
   ManagerShader_T * shader_manager;
   WavefrontLoaderData_T log_data;

   shader_manager = Resource_GetShaderManager();

   // Load Shader
   rend->shader = ManagerShader_Get(shader_manager, "wavefront");

   // Load Models

   WavefrontLoader_Load(&log_data, "assets/log.obj");
   WavefrontLoader_LoadMaterialLibs(&log_data, "assets/");
   WavefrontLoader_LookupMaterial(&log_data);
   WavefrontMesh_Init(&rend->log_mesh, &log_data, "assets/");
   WavefrontLoader_Delete(&log_data);
}

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list)
{
   rend->list = list;
   MapItemListRender_LoadResources(rend);
}

static void MapItemListRender_FreeResources(MapItemListRenderer_T * rend)
{
   WavefrontMesh_Destroy(&rend->log_mesh);
}

void MapItemListRenderer_Destroy(MapItemListRenderer_T * rend)
{
   MapItemListRender_FreeResources(rend);
}



void MapItemListRenderer_Render(MapItemListRenderer_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz)
{
   MapItem_T * list;
   size_t count, i;
   Matrix3D_T temp, translater;


   Shader_Begin(rend->shader);
   Shader_SetLightDirection(rend->shader, lx, ly, lz);


   list = ListMemory_Get(&rend->list->mapitem_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(list[i].item->type == e_IT_Log)
      {
         Matrix3D_SetTranslation(&translater, list[i].x, list[i].y, list[i].z);
         Matrix3D_Multiply(&temp, world, &translater);
         Shader_SetPositionPerspective(rend->shader, &temp, pers);


         WavefrontMesh_Render(&rend->log_mesh, rend->shader->uniforms[e_SU_Samp2D_Texture0]);
      }
   }

   Shader_End(rend->shader);
}

