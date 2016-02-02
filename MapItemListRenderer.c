#include "MapItemListRenderer.h"

#include "WavefrontLoader.h"
#include "WavefrontNode.h"
#include "RenderResources.h"
#include "LogicResources.h"
#include "TypeMap.h"


typedef struct MILR_Element_S MILR_Element_T;

struct MILR_Element_S
{
   int index;
   WavefrontNode_T node;
};

static void MapItemListRenderer_EventCallback(void * object, const TypeMap_T * event)
{
   MapItemListRenderer_T * rend = object;
   MILR_Element_T element;
   int index;

   size_t count, i;
   MILR_Element_T * list;

   if(TypeMap_IsStringEqual(event, "Type", "AddMapItemNotify") == 1)
   {
      element.index = TypeMap_GetInt(event, "Index");
      WavefrontNode_Init(&element.node, rend->scene_graph, &rend->log_mesh);
      SceneGraph_Node_ChildAdd(rend->root_node, WavefrontNode_GetNode(&element.node));
      ArrayList_CopyAlloc(&rend->gfx_list, &element, NULL);
   }
   else if(TypeMap_IsStringEqual(event, "Type", "RemoveMapItemNotify") == 1)
   {
      index = TypeMap_GetInt(event, "Index");
      list = ArrayList_Get(&rend->gfx_list, &count, NULL);
      for(i = 0; i < count; i++)
      {
         if(list[i].index == index)
         {
            SceneGraph_Node_ChildRemove(rend->root_node, WavefrontNode_GetNode(&list[i].node));
            WavefrontNode_Destroy(&list[i].node);
            ArrayList_FreeNow(&rend->gfx_list, i);
            break;
         }
      }

   }

}


static void MapItemListRender_LoadResources(MapItemListRenderer_T * rend)
{
   ManagerShader_T * shader_manager;
   WavefrontLoaderData_T log_data;

   shader_manager = Resources_GetShaderManager();

   // Load Shader
   rend->shader = ManagerShader_Get(shader_manager, "wavefront");

   // Load Models

   WavefrontLoader_Load(&log_data, "assets/log.obj");
   WavefrontLoader_LoadMaterialLibs(&log_data, "assets/");
   WavefrontLoader_LookupMaterial(&log_data);
   WavefrontMesh_Init(&rend->log_mesh, &log_data, "assets/");
   WavefrontLoader_Delete(&log_data);
}

void MapItemListRenderer_Init(MapItemListRenderer_T * rend, MapItemList_T * list, 
                                                            SceneGraph_T * scene_graph)
{
   ManagerEvent_T * event_man;
   event_man = Resources_GetEventManager();
   ManagerEvent_RegisterCallback(event_man, rend, MapItemListRenderer_EventCallback);

   rend->scene_graph = scene_graph;
   rend->root_node = SceneGraph_Node_NewBranch(rend->scene_graph, NULL);
   rend->list = list;
   ArrayList_Init(&rend->gfx_list, sizeof(MILR_Element_T), 0);
   MapItemListRender_LoadResources(rend);
}

static void MapItemListRender_FreeResources(MapItemListRenderer_T * rend)
{
   WavefrontMesh_Destroy(&rend->log_mesh);
}

void MapItemListRenderer_Destroy(MapItemListRenderer_T * rend)
{
   size_t count, i;
   MILR_Element_T * ele;

   ele = ArrayList_Get(&rend->gfx_list, &count, NULL);
   for(i = 0; i < count; i ++)
   {
      WavefrontNode_Destroy(&ele[i].node);
   }

   ArrayList_Destory(&rend->gfx_list);
   
   MapItemListRender_FreeResources(rend);
}


SGNode_T * MapItemListRenderer_GetNode(MapItemListRenderer_T * rend)
{
   return rend->root_node;
}

void MapItemListRenderer_Render(MapItemListRenderer_T * rend)
{
   MapItem_T * list;
   MILR_Element_T * ele_list;
   SGNode_T * node;
   size_t list_count, ele_count, i;
   int index;
   Matrix3D_T temp, translater;


   list = ArrayList_Get(&rend->list->mapitem_list, &list_count, NULL);
   ele_list = ArrayList_Get(&rend->gfx_list, &ele_count, NULL);
   for(i = 0; i < ele_count; i++)
   {
      
      index = ele_list[i].index;
      if(index < list_count)
      {
         node  = WavefrontNode_GetNode(&ele_list[i].node);

         Matrix3D_SetTranslation(&translater, list[index].x, 
               list[index].y, 
               list[index].z);
         SceneGraph_Node_SetMatrix(node, &translater);
      }
      else
      {
         printf("Overdraw!\n");
      }

   }
}

