#ifndef __RENDERQUEUE_H__
#define __RENDERQUEUE_H__
#include <stddef.h>
#include "Shader.h"
#include "GLMesh.h"


typedef struct RenderQueue_S RenerQueue_T;
typedef struct RenderQueueLink_S RenderQueueLink_T;

struct RenderQueueLink_S
{
   Shader_T          * shader;
   void              * shader_state;
   int                 priority;
   RenderQueueLink_T * next;
};

struct RenderQueue_S
{
   RenderQueueLink_T * root;
   size_t count;
  
};


void RenderQueue_Init(RenderQueue_T * queue);
void RenderQueue_Destory(RenderQueue_T * queue);

void RenderQueue_Add(RenderQueue_T * queue, Shader_T * shader, 
                                            void     * shader_state);


void RenderQueue_Flush(RenderQueue_T * queue);

void RenderQueue_Render(RenderQueue_T * queue);


#endif // __RENDERQUEUE_H__


