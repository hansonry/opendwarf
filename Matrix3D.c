#include <math.h>
#include "Matrix3D.h"



#define d(a, b) (a)->data[(b)]

Matrix3D_T * Matrix3D_SetIdentity(Matrix3D_T * matrix)
{
   d(matrix, 0)  = 1; d(matrix, 1)  = 0; d(matrix, 2)  = 0; d(matrix, 3)  = 0;
   d(matrix, 4)  = 0; d(matrix, 5)  = 1; d(matrix, 6)  = 0; d(matrix, 7)  = 0;
   d(matrix, 8)  = 0; d(matrix, 9)  = 0; d(matrix, 10) = 1; d(matrix, 11) = 0;
   d(matrix, 12) = 0; d(matrix, 13) = 0; d(matrix, 14) = 0; d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_SetTranslation(Matrix3D_T * matrix, float x, float y, float z)
{
   d(matrix, 0)  = 1; d(matrix, 1)  = 0; d(matrix, 2)  = 0; d(matrix, 3)  = x;
   d(matrix, 4)  = 0; d(matrix, 5)  = 1; d(matrix, 6)  = 0; d(matrix, 7)  = y;
   d(matrix, 8)  = 0; d(matrix, 9)  = 0; d(matrix, 10) = 1; d(matrix, 11) = z;
   d(matrix, 12) = 0; d(matrix, 13) = 0; d(matrix, 14) = 0; d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_SetXRotation(Matrix3D_T * matrix, float angle)
{
   float c, s;
   c = cos(angle);
   s = sin(angle);
   d(matrix, 0)  = 1; d(matrix, 1)  = 0; d(matrix, 2)  =  0; d(matrix, 3)  = 0;
   d(matrix, 4)  = 0; d(matrix, 5)  = c; d(matrix, 6)  = -s; d(matrix, 7)  = 0;
   d(matrix, 8)  = 0; d(matrix, 9)  = s; d(matrix, 10) =  c; d(matrix, 11) = 0;
   d(matrix, 12) = 0; d(matrix, 13) = 0; d(matrix, 14) =  0; d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_SetYRotation(Matrix3D_T * matrix, float angle)
{
   float c, s;
   c = cos(angle);
   s = sin(angle);
   d(matrix, 0)  =  c; d(matrix, 1)  = 0; d(matrix, 2)  = s; d(matrix, 3)  = 0;
   d(matrix, 4)  =  0; d(matrix, 5)  = 1; d(matrix, 6)  = 0; d(matrix, 7)  = 0;
   d(matrix, 8)  = -s; d(matrix, 9)  = 0; d(matrix, 10) = c; d(matrix, 11) = 0;
   d(matrix, 12) =  0; d(matrix, 13) = 0; d(matrix, 14) = 0; d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_SetZRotation(Matrix3D_T * matrix, float angle)
{
   float c, s;
   c = cos(angle);
   s = sin(angle);
   d(matrix, 0)  = c; d(matrix, 1)  = -s; d(matrix, 2)  = 0; d(matrix, 3)  = 0;
   d(matrix, 4)  = s; d(matrix, 5)  =  c; d(matrix, 6)  = 0; d(matrix, 7)  = 0;
   d(matrix, 8)  = 0; d(matrix, 9)  =  0; d(matrix, 10) = 1; d(matrix, 11) = 0;
   d(matrix, 12) = 0; d(matrix, 13) =  0; d(matrix, 14) = 0; d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_SetRotation(Matrix3D_T * matrix, float x, float y, float z, float angle)
{
   float c = cos(angle);
   float s = sin(angle);
   float C = 1 - c;

   d(matrix, 0)  = x * x * C + c;     d(matrix, 1)  = x * y * C - z * s; d(matrix, 2)  = x * z * C + y * s; d(matrix, 3)  = 0;
   d(matrix, 4)  = y * x * C + z * s; d(matrix, 5)  = y * y * C + c;     d(matrix, 6)  = y * z * C - x * s; d(matrix, 7)  = 0;
   d(matrix, 8)  = z * x * C - y * s; d(matrix, 9)  = z * y * C + x * s; d(matrix, 10) = z * z * C + c;     d(matrix, 11) = 0;
   d(matrix, 12) = 0;                 d(matrix, 13) = 0;                 d(matrix, 14) = 0;                 d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_SetScale(Matrix3D_T * matrix, float x, float y, float z)
{
   d(matrix, 0)  = x; d(matrix, 1)  = 0; d(matrix, 2)  = 0; d(matrix, 3)  = 0;
   d(matrix, 4)  = 0; d(matrix, 5)  = y; d(matrix, 6)  = 0; d(matrix, 7)  = 0;
   d(matrix, 8)  = 0; d(matrix, 9)  = 0; d(matrix, 10) = z; d(matrix, 11) = 0;
   d(matrix, 12) = 0; d(matrix, 13) = 0; d(matrix, 14) = 0; d(matrix, 15) = 1;
   return matrix;
}

Matrix3D_T * Matrix3D_Set(Matrix3D_T * matrix, float rc11, float rc12, float rc13, float rc14,
                                               float rc21, float rc22, float rc23, float rc24,
                                               float rc31, float rc32, float rc33, float rc34,
                                               float rc41, float rc42, float rc43, float rc44)
{
   d(matrix, 0)  = rc11; d(matrix, 1)  = rc12; d(matrix, 2)  = rc13; d(matrix, 3)  = rc14;
   d(matrix, 4)  = rc21; d(matrix, 5)  = rc22; d(matrix, 6)  = rc23; d(matrix, 7)  = rc24;
   d(matrix, 8)  = rc31; d(matrix, 9)  = rc32; d(matrix, 10) = rc33; d(matrix, 11) = rc34;
   d(matrix, 12) = rc41; d(matrix, 13) = rc42; d(matrix, 14) = rc43; d(matrix, 15) = rc44;
   return matrix;
}

Matrix3D_T * Matrix3D_SetArray(Matrix3D_T * matrix, const float * data)
{
   int i;
   for(i = 0; i < MATRIX3D_ARRAY_SIZE; i++)
   {
      d(matrix, i) = data[i];
   }
   return matrix;
}

Matrix3D_T * Matrix3D_Copy(Matrix3D_T * dest, const Matrix3D_T * src)
{
   int i;
   for(i = 0; i < MATRIX3D_ARRAY_SIZE; i++)
   {
      d(dest,i) = d(src, i);
   }
   return dest;
}

Matrix3D_T * Matrix3D_Multiply(Matrix3D_T * dest, const Matrix3D_T * a, const Matrix3D_T * b)
{
   int i, k, x;
   float sum;
   const float *ar, *bc, *ae, *be;
   Matrix3D_T temp;

   ar = a->data;
   bc = b->data;

   x = 0;
   for(i = 0; i < MATRIX3D_ARRAY_SIZE; i++)
   {
      sum = 0;
      ae = ar;
      be = bc;
      for(k = 0; k < 4; k++)
      {
         sum += (*ae) * (*be);
         ae  += 1;
         be  += 4;
      }
      temp.data[i] = sum;
      x++;
      if(x < 4)
      {
         bc ++;
      }
      else
      {         
         bc = b->data;
         ar += 4;
         x = 0;
      }
   }

   for(i = 0; i < MATRIX3D_ARRAY_SIZE; i++)
   {
      d(dest,i) = temp.data[i];
   }

   return dest;
}

Vector3D_T * Matrix3D_ApplyToVector(const Matrix3D_T * matrix, Vector3D_T * dest, const Vector3D_T * src)
{
   Vector3D_T temp;

   temp.x = d(matrix, 0) * src->x + d(matrix, 1) * src->y + d(matrix, 2)  * src->z + d(matrix, 3);
   temp.y = d(matrix, 4) * src->x + d(matrix, 5) * src->y + d(matrix, 6)  * src->z + d(matrix, 7);
   temp.z = d(matrix, 8) * src->x + d(matrix, 9) * src->y + d(matrix, 10) * src->z + d(matrix, 11);

   dest->x = temp.x;
   dest->y = temp.y;
   dest->z = temp.z;
   return dest;
}

#define ToRad(x) ((x) * 3.14f / 180.0f)

Matrix3D_T * Matrix3D_SetProjection(Matrix3D_T * matrix, float fov_degrees, int screen_width, int screen_height, float z_near, float z_far)
{
   const float ar = (float)screen_width / (float)screen_height;
   const float z_range = z_near - z_far;
   const float tan_half_fov = tan(ToRad(fov_degrees / 2.0f));

   d(matrix, 0)  = 1.0f / (tan_half_fov * ar); 
   d(matrix, 1)  = 0.0f; 
   d(matrix, 2)  = 0.0f; 
   d(matrix, 3)  = 0.0f;

   d(matrix, 4)  = 0.0f; 
   d(matrix, 5)  = 1.0f / (tan_half_fov); 
   d(matrix, 6)  = 0.0f; 
   d(matrix, 7)  = 0.0f;

   d(matrix, 8)  = 0.0f; 
   d(matrix, 9)  = 0.0f; 
   d(matrix, 10) = (-z_near - z_far) / z_range; 
   d(matrix, 11) = 2.0f * z_far * z_near / z_range;

   d(matrix, 12) = 0.0f; 
   d(matrix, 13) = 0.0f; 
   d(matrix, 14) = 1.0f; 
   d(matrix, 15) = 0.0f;
   return matrix;
}

