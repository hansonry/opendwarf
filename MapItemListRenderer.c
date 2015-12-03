#include "MapItemListRenderer.h"

#include "WavefrontLoader.h"
#include "Resources.h"


static MapItemListRender_LoadResources(MapItemListRenderer_T * rend)
{
   ManagerShader_T * shader_manager;
   WavefrontLoaderData_T log_data;

   shader_manager = Resource_GetShaderManager();

   // Load Shader
   rend->shader = ManagerShader_Get(shader_manager, "wavefront")->shader_id;
   rend->uniform_pmatrix         = glGetUniformLocation(rend->shader, "PMatrix");
   rend->uniform_wmatrix         = glGetUniformLocation(rend->shader, "WMatrix");
   rend->uniform_light_direction = glGetUniformLocation(rend->shader, "LightDirection");
   rend->uniform_csampler        = glGetUniformLocation(rend->shader, "CSampler");

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

static MapItemListRender_FreeResources(MapItemListRenderer_T * rend)
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
   Matrix3D_T camera, translater, temp;


   glUseProgram(rend->shader);

   glUniform3f(rend->uniform_light_direction, lx, ly, lz);   
   

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   list = ListMemory_Get(&rend->list->mapitem_list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      if(list[i].item->type == e_IT_Log)
      {
         Matrix3D_SetTranslation(&translater, list[i].x, list[i].y, list[i].z);
         Matrix3D_Multiply(&temp, world, &translater);
         Matrix3D_Multiply(&camera, pers, &temp);

         glUniformMatrix4fv(rend->uniform_wmatrix,  1, GL_FALSE, temp.data);
         glUniformMatrix4fv(rend->uniform_pmatrix,  1, GL_FALSE, camera.data);

         WavefrontMesh_Render(&rend->log_mesh, rend->uniform_csampler);
      }
   }


   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}

