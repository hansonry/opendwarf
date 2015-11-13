#ifndef __MATRIXSTACK_H__
#define __MATRIXSTACK_H__

typedef struct MatrixStack_S     MatrixStack_T;
typedef struct MatrixStackLink_S MatrixStackLink_T;

struct MatrixStack_S
{
   MatrixStackLink_T * root;
   Matrix3D_T matrix;
   int depth;
};

void MatrixStack_Init(MatrixStack_T * stack);
void MatrixStack_Destroy(MatrixStack_T * stack);
void MatrixStack_SetIdentity(MatrixStack_T * stack);
void MatrixStack_Set(MatrixStack_T * stack, const Matrix3D_T * matrix);
void MatrixStack_Get(const MatrixStack_T * stack, Matrix3D_T * matrix);
void MatrixStack_Clear(MatrixStack_T * stack);
int  MatrixStack_GetDepth(const MatrixStack_T * stack);
void MatrixStack_Push(MatrixStack_T * stack);
void MatrixStack_Pop(MatrixStack_T * stack);

void MatrixStack_ApplyTranslation(MatrixStack_T * stack, float x, float y, float z);
void MatrixStack_ApplyScale(MatrixStack_T * stack, float sx, float sy, float sz);
void MatrixStack_ApplyXRotation(MatrixStack_T * stack, float angle);
void MatrixStack_ApplyYRotation(MatrixStack_T * stack, float angle);
void MatrixStack_ApplyZRotation(MatrixStack_T * stack, float angle);
void MatrixStack_ApplyRotation(MatrixStack_T * stack, float x, float y, float z, float angle);
void MatrixStack_ApplyMatrix(MatrixStack_T * stack, const Matrix3D_T * matrix);
void MatrixStack_ApplyMatrixPre(MatrixStack_T * stack, const Matrix3D_T * matrix);
void MatrixStack_ApplyMatrixStack(MatrixStack_T * stack, const MatrixStack_T * to_apply);
Vector3D_T * MatrixStack_ApplyToVertex(const MatrixStack_T * stack, Vector3D_T * dest, const Vector3D_T * src);




#endif // __MATRIXSTACK_H__

