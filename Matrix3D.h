#ifndef __MATRIX3D_H__
#define __MATRIX3D_H__

#include "Vector3D.h"

#define MATRIX3D_ARRAY_SIZE 16
typedef struct Matrix3D_S Matrix3D_T;

struct Matrix3D_S
{
   float data[MATRIX3D_ARRAY_SIZE];
};

Matrix3D_T * Matrix3D_SetIdentity(Matrix3D_T * matrix);
Matrix3D_T * Matrix3D_SetTranslation(Matrix3D_T * matrix, float x, float y, float z);
Matrix3D_T * Matrix3D_SetXRotation(Matrix3D_T * matrix, float angle);
Matrix3D_T * Matrix3D_SetYRotation(Matrix3D_T * matrix, float angle);
Matrix3D_T * Matrix3D_SetZRotation(Matrix3D_T * matrix, float angle);
Matrix3D_T * Matrix3D_SetRotation(Matrix3D_T * matrix, float x, float y, float z, float angle);
Matrix3D_T * Matrix3D_SetScale(Matrix3D_T * matrix, float x, float y, float z);
Matrix3D_T * Matrix3D_Set(Matrix3D_T * matrix, float rc11, float rc12, float rc13, float rc14,
                                               float rc21, float rc22, float rc23, float rc24,
                                               float rc31, float rc32, float rc33, float rc34,
                                               float rc41, float rc42, float rc43, float rc44);
Matrix3D_T * Matrix3D_SetArray(Matrix3D_T * matrix, const float * data);
Matrix3D_T * Matrix3D_Copy(Matrix3D_T * dest, const Matrix3D_T * src);
Matrix3D_T * Matrix3D_Multiply(Matrix3D_T * dest, const Matrix3D_T * a, const Matrix3D_T * b);
Vector3D_T * Matrix3D_ApplyToVector(const Matrix3D_T * matrix, Vector3D_T * dest, const Vector3D_T * src);
Matrix3D_T * Matrix3D_SetProjection(Matrix3D_T * matrix, float fov_degrees, int screen_width, int screen_height, float z_near, float z_far);

#endif // __MATRIX3D_H__


