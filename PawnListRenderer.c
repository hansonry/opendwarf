#include "PawnListRenderer.h"

#include "RenderResources.h"
#include "WavefrontLoader.h"

static void PawnListRenderer_LoadResources(PawnListRenderer_T * rend)
{
   ManagerShader_T * shader_manager;
   WavefrontLoaderData_T  pawn_data;
   shader_manager = Resources_GetShaderManager();

   rend->shader = ManagerShader_Get(shader_manager, "wavefront");


   WavefrontLoader_Load(&pawn_data, "assets/pawn1.obj");
   WavefrontLoader_LoadMaterialLibs(&pawn_data, "assets/");
   WavefrontLoader_LookupMaterial(&pawn_data);
   WavefrontMesh_Init(&rend->pawn_mesh, &pawn_data, "assets/");
   WavefrontLoader_Delete(&pawn_data);
   
}

void PawnListRenderer_Init(PawnListRenderer_T * rend, PawnList_T * list)
{
   rend->list = list;
   PawnListRenderer_LoadResources(rend);
}

void PawnListRenderer_Destroy(PawnListRenderer_T * rend)
{
   WavefrontMesh_Destroy(&rend->pawn_mesh);
}


void PawnListRenderer_Render(PawnListRenderer_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz)
{
   Matrix3D_T temp, offset;
   Pawn_T ** plist,* pawn;
   size_t i, count;


   //Shader_Begin(rend->shader);
   //Shader_SetLightDirection(rend->shader, lx, ly, lz);

   plist = ObjectList_Get(&rend->list->pawn_list, &count);

   for(i = 0; i < count; i++)
   {
      pawn = plist[i];
      Matrix3D_SetTranslation(&offset, pawn->cmd_sys.vispos_x, 
                                       pawn->cmd_sys.vispos_y, 
                                       pawn->cmd_sys.vispos_z);
      Matrix3D_Multiply(&temp, world, &offset);
      //Shader_SetPositionPerspective(rend->shader, &temp, pers);
      //WavefrontMesh_Render(&rend->pawn_mesh, rend->shader->uniforms[e_SU_Samp2D_Texture0]);
   }

   //Shader_End(rend->shader);
   

}



