#include "StockPileListRenderer.h"
#include "RenderResources.h"


#define HL 0.5f
#define HL2 0.499f
#define L  1.0f
static const float SquareVertexData[32] =
{
// x    y    z     u  v
   -HL, -HL2,  HL, 0, L, 0, 0, L,
   -HL, -HL2, -HL, 0, L, 0, 0, 0,
    HL, -HL2, -HL, 0, L, 0, L, 0,
    HL, -HL2,  HL, 0, L, 0, L, L
};
#undef HL
#undef L

static const unsigned int SquareIndexData[4] = 
{
   0, 1, 2, 3
};

static void StockPileListRenderer_LoadResources(StockPileListRenderer_T * rend)
{
   const unsigned int section_sizes[3] = {3, 3, 2};
   ManagerShader_T * shader_manager;
   ManagerGLTexture2D_T * text_manager;

   text_manager = Resources_GetTextureManager();
   rend->text = ManagerGLTexture2D_Get(text_manager, "assets/selection.png");
   shader_manager = Resources_GetShaderManager();

   // Load Shader
   rend->shader = (ColorTextureLightShader_T *)ManagerShader_Get(shader_manager, "color_texture_light");

   // Create Mesh
   GLMesh_Init(&rend->mesh, section_sizes,    3,
                            SquareVertexData, 32,
                            SquareIndexData,  4);
   GLMesh_MoveToGFXCard(&rend->mesh);

}

void StockPileListRenderer_Init(StockPileListRenderer_T * rend, StockPileList_T * list)
{
   rend->list = list;
   StockPileListRenderer_LoadResources(rend);
}

static void StockPileListRenderer_FreeResources(StockPileListRenderer_T * rend)
{
   GLMesh_Cleanup(&rend->mesh);
}

void StockPileListRenderer_Destroy(StockPileListRenderer_T * rend)
{
   StockPileListRenderer_FreeResources(rend);
}



void StockPileListRenderer_Render(StockPileListRenderer_T * rend, MatrixStack_T * stack, GFXState_T * gfx_state)
{
   size_t count, i;
   Matrix3D_T temp, translater;
   Position_T * pos_list;

   ColorTextureLightShader_SetColor(rend->shader, 1, 1, 1, 1);

   pos_list = ArrayList_Get(&rend->list->list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      MatrixStack_Push(stack);
      MatrixStack_ApplyTranslation(stack, pos_list[i].x, 
                                          pos_list[i].y, 
                                          pos_list[i].z);
      GFXState_SetWorldMatrix(gfx_state, &stack->matrix);
      ColorTextureLightShader_SetState(rend->shader, gfx_state);
      ColorTextureLightShader_SetMeshAndTexture(rend->shader, rend->text, 
                                                              &rend->mesh, 
                                                              GL_QUADS);

      ColorTextureLightShader_InsertStateToQueue(rend->shader, 1);
         
      MatrixStack_Pop(stack);

   }


}


