#include "PawnListRenderer.h"

#include "RenderResources.h"
#include "WavefrontLoader.h"

static void PawnListRenderer_LoadResources(PawnListRenderer_T * rend)
{
   ManagerShader_T * shader_manager;
   WavefrontLoaderData_T  pawn_data;
   shader_manager = Resources_GetShaderManager();

   rend->shader = (WavefrontShader_T *)ManagerShader_Get(shader_manager, "wavefront");


   WavefrontLoader_Load(&pawn_data, "assets/pawn1.obj");
   WavefrontLoader_LoadMaterialLibs(&pawn_data, "assets/");
   WavefrontLoader_LookupMaterial(&pawn_data);
   WavefrontMesh_Init(&rend->pawn_mesh, &pawn_data, "assets/");
   WavefrontLoader_Delete(&pawn_data);
   
}

void PawnListRenderer_Init(PawnListRenderer_T * rend, PawnList_T * list)
{
   rend->list = list;
   MemoryBlock_Init(&rend->mem_block, sizeof(WavefrontShaderState_T), 0, 0);
   PawnListRenderer_LoadResources(rend);
}

void PawnListRenderer_Destroy(PawnListRenderer_T * rend)
{
   WavefrontMesh_Destroy(&rend->pawn_mesh);
   MemoryBlock_Destroy(&rend->mem_block);
}


void PawnListRenderer_Render(PawnListRenderer_T * rend, RenderQueue_T * render_queue, 
                                                        MatrixStack_T * stack, 
                                                        GFXState_T    * gfx_state)
{
   WavefrontShaderState_T state;
   Matrix3D_T temp, offset;
   Pawn_T ** plist,* pawn;
   size_t i, count;

   MemoryBlock_FreeAll(&rend->mem_block);

   plist = ObjectList_Get(&rend->list->pawn_list, &count);

   for(i = 0; i < count; i++)
   {
      MatrixStack_Push(stack);
      pawn = plist[i];
      
      MatrixStack_ApplyTranslation(stack, pawn->cmd_sys.vispos_x, 
                                          pawn->cmd_sys.vispos_y, 
                                          pawn->cmd_sys.vispos_z);
      GFXState_SetWorldMatrix(gfx_state, &stack->matrix);
      WavefrontShaderState_SetGFXState(&state, gfx_state);
      WavefrontMesh_Render(&rend->pawn_mesh, render_queue, rend->shader, &rend->mem_block, &state, 0);
      MatrixStack_Pop(stack);
   }
}



