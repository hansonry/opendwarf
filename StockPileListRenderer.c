#include "StockPileListRenderer.h"
#include "Resources.h"


#define HL 0.5f
#define HL2 0.499f
#define L  1.0f
static const float SquareVertexData[20] =
{
// x    y    z   u  v
   -HL, -HL2,  HL, 0, L,
   -HL, -HL2, -HL, 0, 0,
    HL, -HL2, -HL, L, 0,
    HL, -HL2,  HL, L, L
};
#undef HL
#undef L

static const unsigned int SquareIndexData[4] = 
{
   0, 1, 2, 3
};

static void StockPileListRenderer_LoadResources(StockPileListRenderer_T * rend)
{
   const unsigned int section_sizes[2] = {3, 2};
   ManagerShader_T * shader_manager;
   ManagerGLTexture2D_T * text_manager;

   text_manager = Resources_GetTextureManager();
   rend->text = ManagerGLTexture2D_Get(text_manager, "assets/selection.png");
   shader_manager = Resource_GetShaderManager();

   // Load Shader
   rend->shader = ManagerShader_Get(shader_manager, "decal");

   // Create Mesh
   GLMesh_Init(&rend->mesh, section_sizes,    2,
                            SquareVertexData, 20,
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



void StockPileListRenderer_Render(StockPileListRenderer_T * rend, const Matrix3D_T * world, const Matrix3D_T * pers, float lx, float ly, float lz)
{
   size_t count, i;
   Matrix3D_T temp, translater;
   Position_T * pos_list;


   Shader_Begin(rend->shader);
   Shader_SetLightDirection(rend->shader, lx, ly, lz);
   Shader_SetTexutre(rend->shader, rend->text, GL_TEXTURE0);


   pos_list = ListMemory_Get(&rend->list->list, &count, NULL);
   for(i = 0; i < count; i++)
   {
      Matrix3D_SetTranslation(&translater, pos_list[i].x, pos_list[i].y, pos_list[i].z);
      Matrix3D_Multiply(&temp, world, &translater);
      Shader_SetPositionPerspective(rend->shader, &temp, pers);
         
      GLMesh_Render(&rend->mesh, GL_QUADS);

   }

   Shader_End(rend->shader);

}


