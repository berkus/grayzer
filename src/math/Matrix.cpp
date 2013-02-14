#include <math.h>
#include "math/Matrix.h"

//───────────────────────────────────────────────────────────────────────────
//
Matrix::Matrix(double v)
{
   int i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         x[i][j] = (i == j) ? v : 0.0;

   x[3][3] = 1.0;
}

//───────────────────────────────────────────────────────────────────────────
//
void Matrix::identity()
{
   int i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         x[i][j] = (i == j) ? 1.0 : 0.0;
}

//───────────────────────────────────────────────────────────────────────────
//
void Matrix::invert()
{
   Matrix out(1);
   int    i, j, k;

   for(i = 0; i < 4; i++)
   {
      double d = x[i][i];

      if(d != 1.0)
      {
         for(j = 0; j < 4; j++)
         {
            out.x[i][j] /= d;
            x[i][j] /= d;
         }
      }
      for(j = 0; j < 4; j++)
      {
         if(j != i)
         {
            if(x[j][i] != 0.0)
            {
               double mulby = x[j][i];

               for(k = 0; k < 4; k++)
               {
                  x[j][k]     -= mulby * x[i][k];
                  out.x[j][k] -= mulby * out.x[i][k];
               }
            }
         }
      }
   }
   *this = out;
}

//───────────────────────────────────────────────────────────────────────────
//
void Matrix::transpose()
{
   double t;
   int    i, j;

   for(i = 0; i < 4; i++)
      for(j = i; j < 4; j++)
         if(i != j)
         {
            t = x[i][j];
            x[i][j]  = x[j][i];
            x[j][i]  = t;
         }
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix& Matrix::operator += (const Matrix& a)
{
   int i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         x[i][j] += a.x[i][j];

   return *this;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix& Matrix::operator -= (const Matrix& a)
{
   int i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         x[i][j] -= a.x[i][j];

   return *this;
}

//───────────────────────────────────────────────────────────────────────────
// Умножение матрицы на скаляр
//
Matrix& Matrix::operator *= (double v)
{
   int i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         x[i][j] *= v;

   return *this;
}

//───────────────────────────────────────────────────────────────────────────
// Умножение матрицы на матрицу
//
Matrix& Matrix::operator *= (const Matrix& a)
{
   Matrix res = *this;
   int    i, j, k;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
      {
         double sum = 0.0;

         for(k = 0; k < 4; k++)
            sum += res.x[i][k] * a.x[k][j];

         x[i][j] = sum;
      }

   return *this;
}

//───────────────────────────────────────────────────────────────────────────
// Сложение матриц
//
Matrix operator + (const Matrix& a, const Matrix& b)
{
   Matrix res;
   int    i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         res.x[i][j] = a.x[i][j] + b.x[i][j];

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix operator - (const Matrix& a, const Matrix& b)
{
   Matrix res;
   int    i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         res.x[i][j] = a.x[i][j] - b.x[i][j];

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix operator * (const Matrix& a, const Matrix& b)
{
   Matrix res;
   int    i, j, k;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
      {
         double sum = 0.0;

         for(k = 0; k < 4; k++)
            sum += a.x[i][k] * b.x[k][j];

         res.x[i][j] = sum;
      }

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix operator * (const Matrix& a, double v)
{
   Matrix res;
   int    i, j;

   for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++)
         res.x[i][j] = a.x[i][j] * v;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
// Умножение матрицы на вектор
//
Vector operator * (const Matrix& M, const Vector& v)
{
   Vector res;

   res.x = v.x*M.x[0][0] + v.y*M.x[1][0] + v.z*M.x[2][0] + M.x[3][0];
   res.y = v.x*M.x[0][1] + v.y*M.x[1][1] + v.z*M.x[2][1] + M.x[3][1];
   res.z = v.x*M.x[0][2] + v.y*M.x[1][2] + v.z*M.x[2][2] + M.x[3][2];

   double denom = v.x*M.x[0][3] + v.y*M.x[1][3] + v.z*M.x[2][3] + M.x[3][3];

   // normalize
   if(denom != 1.0) res /= denom;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
// Матрица переноса на вектор loc
//
Matrix translate(const Vector& loc)
{
   Matrix res(1);

   res.x[3][0] = loc.x;
   res.x[3][1] = loc.y;
   res.x[3][2] = loc.z;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
// Матрица обратного переноса на вектор -loc
//
Matrix inv_translate(const Vector& loc)
{
   Matrix res(1);

   res.x[3][0] = 0.0 - loc.x;
   res.x[3][1] = 0.0 - loc.y;
   res.x[3][2] = 0.0 - loc.z;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix scale(const Vector& v)
{
   Matrix res(1);

   res.x[0][0] = fabs(v.x);
   res.x[1][1] = fabs(v.y);
   res.x[2][2] = fabs(v.z);

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix inv_scale(const Vector& v)
{
   Matrix res(1);

   res.x[0][0] = fabs(1.0 / v.x);
   res.x[1][1] = fabs(1.0 / v.y);
   res.x[2][2] = fabs(1.0 / v.z);

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix rotate_x(double angle)
{
   Matrix res(1);
   double cosine = cos(angle);
   double sine   = sin(angle);

   res.x[1][1] = cosine;
   res.x[2][1] = -sine;
   res.x[1][2] = sine;
   res.x[2][2] = cosine;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix rotate_y(double angle)
{
   Matrix res(1);
   double cosine = cos(angle);
   double sine   = sin(angle);

   res.x[0][0] = cosine;
   res.x[2][0] = -sine;
   res.x[0][2] = sine;
   res.x[2][2] = cosine;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix rotate_z(double angle)
{
   Matrix res(1);
   double cosine = cos(angle);
   double sine   = sin(angle);

   res.x[0][0] = cosine;
   res.x[1][0] = -sine;
   res.x[0][1] = sine;
   res.x[1][1] = cosine;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
// Матрица вращения вокруг оси axis на угол angle
//
Matrix rotation(const Vector& axis, double angle)
{
   Matrix res(1);
   double Cosine = cos(angle);
   double Sine   = sin(angle);

   res.x[0][0] = axis.x * axis.x + (1 - axis.x * axis.x) * Cosine;
   res.x[0][1] = axis.x * axis.y * (1 - Cosine) + axis.z * Sine;
   res.x[0][2] = axis.x * axis.z * (1 - Cosine) - axis.y * Sine;
   res.x[0][3] = 0;

   res.x[1][0] = axis.x * axis.y * (1 - Cosine) - axis.z * Sine;
   res.x[1][1] = axis.y * axis.y + (1 - axis.y * axis.y) * Cosine;
   res.x[1][2] = axis.y * axis.z * (1 - Cosine) + axis.x * Sine;
   res.x[1][3] = 0;

   res.x[2][0] = axis.x * axis.z * (1 - Cosine) + axis.y * Sine;
   res.x[2][1] = axis.y * axis.z * (1 - Cosine) - axis.x * Sine;
   res.x[2][2] = axis.z * axis.z + (1 - axis.z * axis.z) * Cosine;
   res.x[2][3] = 0;

   // not needed!
   res.x[3][0] = 0;
   res.x[3][1] = 0;
   res.x[3][2] = 0;
   res.x[3][3] = 1;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix mirror_x()
{
   Matrix res(1);

   res.x[0][0] = -1;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix mirror_y()
{
   Matrix res(1);

   res.x[1][1] = -1;

   return res;
}

//───────────────────────────────────────────────────────────────────────────
//
Matrix mirror_z()
{
   Matrix res(1);

   res.x[2][2] = -1;

   return res;
}
