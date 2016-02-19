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
   MemoryBlock_Init(&rend->mem_block, sizeof(ColorTextureLightShaderState_T), 0, 0);
   StockPileListRenderer_LoadResources(rend);
}

static void StockPileListRenderer_FreeResources(StockPileListRenderer_T * rend)
{
   GLMesh_Cleanup(&rend->mesh);
}

void StockPileListRenderer_Destroy(StockPileListRenderer_T * rend)
{
   StockPileListRenderer_FreeResources(rend);
   MemoryBlock_Destroy(&rend->mem_block);
}



void StockPileListRenderer_Render(StockPileListRenderer_T * rend, RenderQueue_T * render_queue, 
                                                                  MatrixStack_T * stack, 
                                                                  GFXState_T    * gfx_state)
{
   size_t count, i;
   ColorTextureLightShaderState_T * state;
   Matrix3D_T temp, translater;
   StockPile_T * stock_rc;

   MemoryBlock_FreeAll(&rend->mem_block);

   count = ObjectList_Count(&rend->list->list);
   for(i = 0; i < count; i++)
   {
      stock_rc = ObjectList_Get(&rend->list->list, i);
      MatrixStack_Push(stack);
      MatrixStack_ApplyTranslation(stack, stock_rc->pos.x, 
                                          stock_rc->pos.y, 
                                          stock_rc->pos.z);
      GFXState_SetWorldMatrix(gfx_state, &stack->matrix);


      state = MemoryBlock_Allocate(&rend->mem_block);
      ColorTextureLightShaderState_SetColor(state, 1, 1, 1, 1);
      ColorTextureLightShaderState_SetGFXState(state, gfx_state);
      ColorTextureLightShaderState_SetMeshAndTexture(state, rend->text, 
                                                            &rend->mesh, 
                                                            GL_QUADS);


      RenderQueue_Add(render_queue, &rend->shader->parent, state, 1);
         
      MatrixStack_Pop(stack);

   }


}


