#include <math.h>
#include "Vector3D.h"

Vector3D_T * Vector3D_Set(Vector3D_T * vect, float x, float y, float z)
{
   vect->x = x;
   vect->y = y;
   vect->z = z;
   return vect;
}
Vector3D_T * Vector3D_SetArray(Vector3D_T * vect, const float * array)
{
   vect->x = array[0];
   vect->y = array[1];
   vect->z = array[2];
   return vect;
}
float * Vector3D_GetArray(const Vector3D_T * vect, float * array)
{
   array[0] = vect->x;
   array[1] = vect->y;
   array[2] = vect->z;
   return array;
}
Vector3D_T * Vector3D_Copy(Vector3D_T * dest, const Vector3D_T * src)
{
   dest->x = src->x;
   dest->y = src->y;
   dest->z = src->z;
   return dest;
}
float Vector3D_Distance(const Vector3D_T * vect)
{
   float dist2;
   dist2 = vect->x * vect->x +
           vect->y * vect->y +
           vect->z * vect->z;
   return (float)sqrt(dist2);
}
float Vector3D_Distance2(const Vector3D_T * vect)
{
   float dist2;
   dist2 = vect->x * vect->x +
           vect->y * vect->y +
           vect->z * vect->z;
   return dist2;
}

Vector3D_T * Vector3D_Normalize(Vector3D_T * dest, const Vector3D_T * src)
{
   float dist2, dist;
   dist2 = src->x * src->x +
           src->y * src->y +
           src->z * src->z;
   dist = (float)sqrt(dist2);

   dest->x = src->x / dist;
   dest->y = src->y / dist;
   dest->z = src->z / dist;
   return dest;
}

Vector3D_T * Vector3D_Add(Vector3D_T * dest, const Vector3D_T * a, const Vector3D_T * b)
{
   dest->x = a->x + b->x;
   dest->y = a->y + b->y;
   dest->z = a->z + b->z;
   return dest;
}

Vector3D_T * Vector3D_Subtract(Vector3D_T * dest, const Vector3D_T * a, const Vector3D_T * b)
{
   dest->x = a->x - b->x;
   dest->y = a->y - b->y;
   dest->z = a->z - b->z;
   return dest;
}

float Vector3D_Dot(const Vector3D_T * a, const Vector3D_T * b)
{
   return a->x * b->x + a->y * b->y + a->z * b->z;
}

Vector3D_T * Vector3D_Cross(Vector3D_T * dest, const Vector3D_T * a, const Vector3D_T * b)
{
   Vector3D_T t;
   t.x = a->y * b->z - a->z * b->y;
   t.y = a->z * b->x - a->x * b->z;
   t.z = a->x * b->y - a->y * b->x;

   dest->x = t.x;
   dest->y = t.y;
   dest->z = t.z;
   return dest;
}

