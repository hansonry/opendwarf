#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

typedef struct Vector3D_S Vector3D_T;
struct Vector3D_S
{
   float x;
   float y;
   float z;
};

Vector3D_T * Vector3D_Set(Vector3D_T * vect, float x, float y, float z);
Vector3D_T * Vector3D_SetArray(Vector3D_T * vect, const float * array);
float * Vector3D_GetArray(const Vector3D_T * vect, float * array);
Vector3D_T * Vector3D_Copy(Vector3D_T * dest, const Vector3D_T * src);
float Vector3D_Distance(const Vector3D_T * vect);
float Vector3D_Distance2(const Vector3D_T * vect);
Vector3D_T * Vector3D_Normalize(Vector3D_T * dest, const Vector3D_T * src);
Vector3D_T * Vector3D_Add(Vector3D_T * dest, const Vector3D_T * a, const Vector3D_T * b);
Vector3D_T * Vector3D_Subtract(Vector3D_T * dest, const Vector3D_T * a, const Vector3D_T * b);
float Vector3D_Dot(const Vector3D_T * a, const Vector3D_T * b);
Vector3D_T * Vector3D_Cross(Vector3D_T * dest, const Vector3D_T * a, const Vector3D_T * b);

#endif // __VECTOR3D_H__

