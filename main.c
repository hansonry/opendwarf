#include <stdio.h>
#include <math.h>
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "CEngine.h"
#include "FloatWriter.h"
#include "UIntWriter.h"
#include "ShaderTool.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MatrixStack.h"
#include "GLMesh.h"
#include "GLMeshBuilder.h"
#include "UnitCube.h"
#include "GLTexture2D.h"
#include "SDL2/SDL_ttf.h"
#include "GLFont.h"
#include "GLCam_FPS.h"
#include "MapChunk.h"
#include "MapChunkRender.h"
#include "WavefrontLoader.h"
#include "WavefrontMesh.h"
#include "MapItemListRenderer.h"
#include "MapItemList.h"
#include "Item.h"
#include "Resources.h"
#include "PawnListRenderer.h"
#include "StockPileListRenderer.h"
#include "ItemList.h"
#include "MapRay.h"
#include "JobManager.h"
#include "GFXState.h"
#include "SceneGraph.h"
#include "WavefrontNode.h"

static void gl_init(void);

static void game_setup(CEngine_T * engine);
static void game_cleanup(CEngine_T * engine);
static void game_update(CEngine_T * engine, float seconds);
static void game_render(CEngine_T * engine);
static void game_input(CEngine_T * engine, SDL_Event * event);

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600


int main(int args, char * argc[])
{
   CEngine_T engine;
   CEngine_Init(&engine, "opendwarf", SCREEN_WIDTH, SCREEN_HEIGHT,
                         game_setup, 
                         game_cleanup, 
                         game_update, 
                         game_render, 
                         game_input,
                         CENGINE_FLAG_AUTOCLOSE);
   CEngine_Start(&engine);
   //WavefrontLoader_TEST();
   printf("End\n");
   return 0;
}



// open dwarf
MapChunk_T map_chunk;
MapChunk_T visible_map_chunk;
MapChunkRender_T map_chunk_render;
MapItemList_T map_item_list;
MapItemListRenderer_T map_item_list_renderer;
PawnList_T pawn_list;
PawnListRenderer_T pawn_list_renderer;
StockPileList_T stockpile_list;
StockPileListRenderer_T stockpile_list_renderer;
ItemList_T item_list;
JobManager_T job_manager;
SceneGraph_T scene_graph;

// other
WavefrontMesh_T log_mesh;
UnitCube_T cube;
WavefrontNode_T wavefront_node;

GLTexture2D_T * test_text, font_text;
GLFont_T font_hanken;
GLCam_FPS_T fps_cam;
int cam_drag;
Shader_T *shader_test1, *shader_wavefront;
float angle;
Matrix3D_T projection;
MatrixStack_T m_stack;


float px, py;
float a2;

static void mapchunk_setup(void)
{
   MapChunkTile_T tile_air, tile_grass, tile_rock;
   PositionSet_T pset;
   Position_T ps, pe;
   tile_air.material = e_MCTM_None;
   tile_air.topology = e_MCTT_None;

   tile_grass.material = e_MCTM_Grass;
   tile_grass.topology = e_MCTT_Block;
   
   tile_rock.material = e_MCTM_Rock;
   tile_rock.topology = e_MCTT_Block;

   MapChunk_Init(&map_chunk, 5, 5, 5);
   MapChunk_Init(&visible_map_chunk, 5, 5, 5);
   MapChunk_FillAllUnknown(&visible_map_chunk);

   MapChunk_Fill(&map_chunk, 0, 0, 0, 4, 4, 4, &tile_air);
   MapChunk_Fill(&map_chunk, 0, 0, 0, 4, 1, 4, &tile_grass);
   MapChunk_Set(&map_chunk, 2, 2, 2, &tile_rock);
   MapChunk_Set(&map_chunk, 0, 2, 4, &tile_rock);
   MapChunk_Set(&map_chunk, 2, 2, 3, &tile_rock);


   
   MapChunkRender_Init(&map_chunk_render, &visible_map_chunk);

   PositionSet_Init(&pset);

   Position_Set(&ps, 0, 4, 0);
   Position_Set(&pe, 2, 3, 4);
   MapRay_Cast(&pset, &map_chunk, &ps, &pe);
   PositionSet_Desstroy(&pset);

}

#include "MapItemEvent.h"
static void Item_Setup(SGNode_T * root_node)
{
   Item_T * item;
   TypeMap_T event;
   Position_T pos;
   Position_T d_pos;
   ManagerEvent_T * man_event;
   
   man_event = Resources_GetEventManager();   

   ItemList_Init(&item_list);

   MapItemList_Init(&map_item_list);
   MapItemListRenderer_Init(&map_item_list_renderer, &map_item_list, &scene_graph);
   SceneGraph_Node_ChildAdd(root_node, MapItemListRenderer_GetNode(&map_item_list_renderer));

   item = ItemList_Add(&item_list); 
   Item_Init(item, e_IT_Log);
  
   TypeMap_Init(&event);   
   Position_Set(&pos, 0, 2, 0);
   MapItemEvent_AddMapItemRequest_Init(&event, item, &pos);
   ManagerEvent_SendEvent(man_event, &event);

   item = ItemList_Add(&item_list);
   Item_Init(item, e_IT_Log);
  
   Position_Set(&pos, 1, 2, 0);
   MapItemEvent_AddMapItemRequest_Init(&event, item, &pos);
   ManagerEvent_SendEvent(man_event, &event);
   TypeMap_Destory(&event);


   Position_Set(&pos, 1, 2, 0);
   Position_Set(&d_pos, 4, 2, 4);
}

static void Pawn_Setup(void)
{
   Pawn_T * pawn;
   Position_T  pos;
   PawnList_Init(&pawn_list);
   PawnListRenderer_Init(&pawn_list_renderer, &pawn_list);

   pawn = PawnList_Add(&pawn_list);
   Pawn_Init(pawn, &map_chunk, &map_item_list);
}

#include "StockPileEvent.h"
static void StockPile_Setup(void)
{
   Position_T  pos;
   ManagerEvent_T * event_man;
   TypeMap_T event;

   event_man = Resources_GetEventManager();


   StockPileList_Init(&stockpile_list);
   StockPileListRenderer_Init(&stockpile_list_renderer, &stockpile_list);

   
   TypeMap_Init(&event);

   
   Position_Set(&pos, 4, 2, 4);
   StockPileEvent_CreateStockpile_Init(&event, &pos);
   ManagerEvent_SendEvent(event_man, &event);

   
   Position_Set(&pos, 4, 2, 3);
   StockPileEvent_CreateStockpile_Init(&event, &pos);
   ManagerEvent_SendEvent(event_man, &event);

   TypeMap_Destory(&event);
}

static void game_setup(CEngine_T * engine)
{
   WavefrontLoaderData_T log_data;
   ManagerShader_T * shader_manager;
   ManagerGLTexture2D_T * texture_manager;
   SGNode_T * root_node;
   Matrix3D_T matrix;
   Resources_Init();
   shader_manager = Resources_GetShaderManager();
   texture_manager = Resources_GetTextureManager();
   gl_init();
   MatrixStack_Init(&m_stack);


   // SceneGraph
   SceneGraph_Init(&scene_graph);
   root_node = SceneGraph_Node_NewBranch(&scene_graph, NULL);
   SceneGraph_SetRootNode(&scene_graph, root_node);
   Matrix3D_SetTranslation(&matrix, 0, 0, 10);
   SceneGraph_Node_SetMatrix(root_node, &matrix);

   // Cube

   UnitCube_Init(&cube);

   // Shader
   shader_test1 = ManagerShader_Get(shader_manager, "test1");
   shader_wavefront = ManagerShader_Get(shader_manager, "wavefront");



   // Projection Matrix
   Matrix3D_SetProjection(&projection, 30, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 100);

   // Textures
   test_text = ManagerGLTexture2D_Get(texture_manager, "testImage1024.png");

   // Kin
   px = 0;
   py = 0;
   a2 = 0;

   // Font Test
   GLFont_Init(&font_hanken, "Hanken-Book.ttf", 16);
   GLFont_CreateGLTexture(&font_hanken, &font_text, "Hello", 1, 0, 0, 1);

   // FPS Camera
   GLCam_FPS_Init(&fps_cam);
   cam_drag = 0;

   // Mesh Test
   WavefrontLoader_Load(&log_data, "assets/pawn1.obj");
   WavefrontLoader_LoadMaterialLibs(&log_data, "assets/");
   WavefrontLoader_LookupMaterial(&log_data);
   WavefrontMesh_Init(&log_mesh, &log_data, "assets/");
   WavefrontLoader_Delete(&log_data);

   WavefrontNode_Init(&wavefront_node, &scene_graph, &log_mesh);
   
   SceneGraph_Node_ChildAdd(root_node, WavefrontNode_GetNode(&wavefront_node)); 
   

   // open dwarf
   mapchunk_setup();
   Item_Setup(root_node);
   Pawn_Setup();
   StockPile_Setup();

   JobManager_Init(&job_manager, &pawn_list, &map_item_list, &stockpile_list);

}

static void game_cleanup(CEngine_T * engine)
{
   MatrixStack_Destroy(&m_stack);
   UnitCube_Cleanup(&cube);

   // Font Test
   GLFont_Destory(&font_hanken);
   GLTexture2D_Destroy(&font_text);

   // Mesh test
   WavefrontMesh_Destroy(&log_mesh);

   // open dwarf
   MapChunkRender_Destroy(&map_chunk_render);
   MapChunk_Destroy(&map_chunk);

   MapItemListRenderer_Destroy(&map_item_list_renderer);
   MapItemList_Destory(&map_item_list);

   PawnListRenderer_Destroy(&pawn_list_renderer);
   PawnList_Destroy(&pawn_list);

   StockPileListRenderer_Destroy(&stockpile_list_renderer);
   StockPileList_Destroy(&stockpile_list);

   ItemList_Destroy(&item_list);

   JobManager_Destroy(&job_manager);
 

   WavefrontNode_Destroy(&wavefront_node);
   SceneGraph_Destroy(&scene_graph);
   Resources_Cleanup();
}

static void game_update(CEngine_T * engine, float seconds)
{
   size_t count;
   Position_T * pos_list;
   angle = angle + 3.14f / 4.0f * seconds;
   a2 += seconds;
   px = cos(a2) * 2;
   py = sin(a2) * 2;
   if(cam_drag == 1)
   {
      int dx, dy;
      SDL_GetRelativeMouseState(&dx, &dy);
      //printf("(dx, dy): (%i, %i)\n", dx, dy);
      GLCam_FPS_Mouse(&fps_cam, dx, dy);

   }

   GLCam_FPS_Update(&fps_cam, seconds);
   PawnList_Update(&pawn_list, seconds);


   pos_list = PawnList_GetVisibilityList(&pawn_list, &count);
   MapChunk_CopyData(&visible_map_chunk, &map_chunk, pos_list, count);

   JobManager_Update(&job_manager, seconds);
}

static void game_render(CEngine_T * engine)
{
   Matrix3D_T matrix, temp;
   GFXState_T gfx_state;
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   MatrixStack_Clear(&m_stack);
   GFXState_Init(&gfx_state);

   GLCam_FPS_Render(&fps_cam, &m_stack);
   MatrixStack_Get(&m_stack, &temp);
   GFXState_SetCameraMatrix(&gfx_state, &temp);
   GFXState_SetPerspectiveMatrix(&gfx_state, &projection);
   GFXState_SetLightSun1DirectionAndColor(&gfx_state, 0.557, 0.557f, -0.557f, 1, 1, 1);

   /*
   glBegin( GL_QUADS ); 
   glVertex2f( -0.5f, -0.5f ); 
   glVertex2f( 0.5f, -0.5f ); 
   glVertex2f( 0.5f, 0.5f ); 
   glVertex2f( -0.5f, 0.5f ); 
   glEnd();
   */



   Matrix3D_SetIdentity(&matrix);

   MatrixStack_ApplyTranslation(&m_stack, 0,  0,  10);


   //UnitCube_Render(&cube);
   MapChunkRender_Render(&map_chunk_render, &m_stack.matrix, &projection, 0.577f, 0.577f, -0.577f);
   MapItemListRenderer_Render(&map_item_list_renderer);
   PawnListRenderer_Render(&pawn_list_renderer, &m_stack.matrix, &projection, 0.577f, 0.577f, -0.577f);
   StockPileListRenderer_Render(&stockpile_list_renderer, &m_stack.matrix, &projection, 0.577f, 0.577f, -0.577f);







   MatrixStack_ApplyTranslation(&m_stack, px, py, 0);
   MatrixStack_ApplyYRotation(&m_stack, angle);

   SceneGraph_Node_SetMatrix(WavefrontNode_GetNode(&wavefront_node), &m_stack.matrix);

   // Mesh Test

   //Shader_Use(shader_wavefront);
   //Shader_Setup(shader_wavefront, &gfx_state);
   //Shader_SetLightDirection(shader_wavefront, 0.577f, 0.577f, -0.577f);
   //WavefrontMesh_Render(&log_mesh, shader_wavefront->uniforms[e_SU_Samp2D_Texture0]);
   // open dwarf
   
   SceneGraph_Render(&scene_graph, &gfx_state);


   GFXState_Destory(&gfx_state);
}

static void game_input(CEngine_T * engine, SDL_Event * event)
{
   int key_state, key_state_change;
   if(event->type == SDL_KEYDOWN)
   {
      key_state        = 1;
      key_state_change = 1;
   }
   else if(event->type == SDL_KEYUP)
   {
      key_state        = 0;
      key_state_change = 1;
   }
   else
   {
      key_state_change = 0;
   }

   if(key_state_change == 1)
   {
      if(event->key.keysym.sym == SDLK_w)      GLCam_FPS_Keyboard(&fps_cam, e_fck_forward,  key_state);
      if(event->key.keysym.sym == SDLK_s)      GLCam_FPS_Keyboard(&fps_cam, e_fck_backward, key_state);
      if(event->key.keysym.sym == SDLK_a)      GLCam_FPS_Keyboard(&fps_cam, e_fck_left,     key_state);
      if(event->key.keysym.sym == SDLK_d)      GLCam_FPS_Keyboard(&fps_cam, e_fck_right,    key_state);
      if(event->key.keysym.sym == SDLK_LSHIFT) GLCam_FPS_Keyboard(&fps_cam, e_fck_run,      key_state);
   }         


   if(event->type == SDL_MOUSEBUTTONDOWN)
   {
      cam_drag = 1;            
      SDL_GetRelativeMouseState(NULL, NULL); // Flush previous delta points
   }
   else if(event->type == SDL_MOUSEBUTTONUP)
   {
      cam_drag = 0;
   }
}


static void gl_init(void)
{

   GLMeshBuilder_T builder;

   float vdata[12];
   unsigned int mdata[4];
   float n;

   glewInit();

   //Initialize clear color 
   glClearColor( 0.f, 0.f, 0.f, 1.f ); 
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);
   glEnable(GL_DEPTH_TEST);



}



