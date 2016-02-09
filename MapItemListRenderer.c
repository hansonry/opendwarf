#include "MapItemListRenderer.h"

#include "WavefrontLoader.h"
#include "RenderResources.h"
#include "LogicResources.h"
#include "TypeMap.h"



static void MapItemListRenderer_EventCallback(void * object, const TypeMap_T * event)
{
   MapItemListRenderer_T * rend = object;
   /*

   if(TypeMap_IsStringEqual(event, "Type", "AddMapItemNotify") == 1)
   {
   }
   else if(TypeMap_IsStringEqual(event, "Type", "RemoveMapItemNotify") == 1)
   {
   }
   */

}


static void MapItemListRender_LoadResources(MapItemListRenderer_T * rend)
{
   ManagerShader_T * shader_manager;
   WavefrontLoaderData_T log_data;

   shader_manager = Resources_GetShaderManager();

   // Load Shader
   rend->shader = (WavefrontShader_T *)ManagerShader_Get(shader_manager, "wavefront");

   // Load Models

   WavefrontLoader_Load(&log_data, "assets/log.obj");
   WavefrontLoader_LoadMaterialLibs(&log_data, "assets/");
   WavefrontLoader_LookupMaterial(&log_data);
   WavefrontMesh_Init(&rend->log_mesh, &log_data, "assets/");
   WavefrontLoader_Delete(&log_data);
}

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list)
{
   ManagerEvent_T * event_man;
   event_man = Resources_GetEventManager();
   ManagerEvent_RegisterCallback(event_man, rend, MapItemListRenderer_EventCallback);

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


void MapItemListRenderer_Render(MapItemListRenderer_T * rend, MatrixStack_T * stack, 
                                                              GFXState_T * gfx_state)
{
   MapItem_T * list;
   size_t list_count, i;
   int index;
   Matrix3D_T temp, translater;

   list = ArrayList_Get(&rend->list->mapitem_list, &list_count, NULL);
   for(i = 0; i < list_count; i++)
   {
         MatrixStack_Push(stack);
         MatrixStack_ApplyTranslation(stack, list[i].x, 
                                             list[i].y, 
                                             list[i].z);

         GFXState_SetWorldMatrix(gfx_state, &stack->matrix);
         WavefrontShader_SetState(rend->shader, gfx_state);

         WavefrontMesh_Render(&rend->log_mesh, rend->shader, 0);
         MatrixStack_Pop(stack);
   }
}

