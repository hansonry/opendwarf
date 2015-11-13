#include <stdio.h>
#include <stdlib.h>
#include "Vector3D.h"
#include "Matrix3D.h"
#include "MatrixStack.h"


struct MatrixStackLink_S
{
   Matrix3D_T matrix;
   MatrixStackLink_T * next;
};


void MatrixStack_Init(MatrixStack_T * stack)
{
   stack->depth = 0;
   stack->root = NULL;
   Matrix3D_SetIdentity(&stack->matrix);
}

void MatrixStack_Destroy(MatrixStack_T * stack)
{
   MatrixStack_Clear(stack);
}

void MatrixStack_SetIdentity(MatrixStack_T * stack)
{
   Matrix3D_SetIdentity(&stack->matrix);
}

void MatrixStack_Set(MatrixStack_T * stack, const Matrix3D_T * matrix)
{
   Matrix3D_Copy(&stack->matrix, matrix);
}

void MatrixStack_Get(const MatrixStack_T * stack, Matrix3D_T * matrix)
{
   Matrix3D_Copy(matrix, &stack->matrix);
}
void MatrixStack_Clear(MatrixStack_T * stack)
{
   MatrixStackLink_T * loop, *temp;
   loop = stack->root;
   while(loop != NULL)
   {
      temp = loop;
      loop = loop->next;

      free(temp);
   }

   stack->depth = 0;
   stack->root = NULL;
   Matrix3D_SetIdentity(&stack->matrix);
}

int  MatrixStack_GetDepth(const MatrixStack_T * stack)
{
   return stack->depth;
}
void MatrixStack_Push(MatrixStack_T * stack)
{
   MatrixStackLink_T *link;

   link = malloc(sizeof(MatrixStackLink_T));
   link->next = stack->root;
   stack->root = link;
   stack->depth ++;
   Matrix3D_Copy(&link->matrix, &stack->matrix);

}

void MatrixStack_Pop(MatrixStack_T * stack)
{
   if(stack->root != NULL && stack->depth > 0)
   {
      Matrix3D_Copy(&stack->matrix, &stack->root->matrix);
      stack->root = stack->root->next;
      stack->depth --;
   }
   else
   {
      printf("Error: MatrixStack_Pop Can't Pop because nothing in stack: %p\n", stack);
   }
}

void MatrixStack_ApplyTranslation(MatrixStack_T * stack, float x, float y, float z)
{
   Matrix3D_T local;
   Matrix3D_SetTranslation(&local, x, y, z);
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &local);
}

void MatrixStack_ApplyScale(MatrixStack_T * stack, float sx, float sy, float sz)
{
   Matrix3D_T local;
   Matrix3D_SetScale(&local, sx, sy, sz);
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &local);
}

void MatrixStack_ApplyXRotation(MatrixStack_T * stack, float angle)
{
   Matrix3D_T local;
   Matrix3D_SetXRotation(&local, angle);
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &local);
}

void MatrixStack_ApplyYRotation(MatrixStack_T * stack, float angle)
{
   Matrix3D_T local;
   Matrix3D_SetYRotation(&local, angle);
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &local);
}

void MatrixStack_ApplyZRotation(MatrixStack_T * stack, float angle)
{
   Matrix3D_T local;
   Matrix3D_SetZRotation(&local, angle);
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &local);
}

void MatrixStack_ApplyRotation(MatrixStack_T * stack, float x, float y, float z, float angle)
{
   Matrix3D_T local;
   Matrix3D_SetRotation(&local, x, y, z, angle);
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &local);
}

void MatrixStack_ApplyMatrix(MatrixStack_T * stack, const Matrix3D_T * matrix)
{
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, matrix);
}

void MatrixStack_ApplyMatrixPre(MatrixStack_T * stack, const Matrix3D_T * matrix)
{
   Matrix3D_Multiply(&stack->matrix, matrix, &stack->matrix);
}

void MatrixStack_ApplyMatrixStack(MatrixStack_T * stack, const MatrixStack_T * to_apply)
{
   Matrix3D_Multiply(&stack->matrix, &stack->matrix, &to_apply->matrix);
}



Vector3D_T * MatrixStack_ApplyToVertex(const MatrixStack_T * stack, Vector3D_T * dest, const Vector3D_T * src)
{
   return Matrix3D_ApplyToVector(&stack->matrix, dest, src);
}



