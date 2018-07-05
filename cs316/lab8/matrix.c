/*
   matrix.c: simple 4x4 matrix library with 2D functions
   Created by: Kevin Sahr, 10/31/17

   4x4 matrix layout in memory:

      m0  m4  m8  m12
      m1  m5  m9  m13
      m2  m6 m10  m14
      m3  m7 m11  m15

*/

#include <math.h>
#include <stdio.h>
#include "matrix.h" 

void printMatrix (Matrix m) {
   int r, c;
   for (r = 0; r < MATRIX_DIM; r++) {
      printf("  ");
      for (c = 0; c < MATRIX_DIM; c++)
         printf(" %6.3f", m[r + MATRIX_DIM * c]); // count by 4's
      printf("\n");
   }
}

void setIdentityMatrix (Matrix m) {
   int i;
   for (i = 0; i < MATRIX_DIM * MATRIX_DIM; i++) m[i] = 0.0;
   m[0] = m[5] = m[10] = m[15] = 1.0;
}
   
void setScale2dMatrix (Matrix m, GLfloat sx, GLfloat sy) {
   setIdentityMatrix(m);
   m[0] = sx;
   m[5] = sy;
}
   
void setRotate2dMatrix (Matrix m, GLfloat thetaRads) {
   setIdentityMatrix(m);
   m[0] = m[5] = cos(thetaRads);
   m[1] = sin(thetaRads);
   m[4] = -1.0 * m[1];
}
   
void setTranslate2dMatrix (Matrix m, GLfloat tx, GLfloat ty) {
   setIdentityMatrix(m);
   m[12] = tx;
   m[13] = ty;
}
   
void setOrtho2dMatrix (Matrix m, GLfloat left, GLfloat right,
                        GLfloat bottom, GLfloat top) {
   setIdentityMatrix(m);

   m[0] = 2.0 / (right - left);
   m[5] = 2.0 / (top - bottom);
   GLfloat tx = (right + left) / (right - left);
   GLfloat ty = (top + bottom) / (top - bottom);
   m[12] = tx;
   m[13] = ty;
}

void setTranslateMatrix (Matrix m, const Vec3D* trans) {
   setIdentityMatrix(m);
   m[12] = trans->x;
   m[13] = trans->y;
   m[14] = trans->z;
}

void setScaleMatrix (Matrix m, const Vec3D* scale) {
   setIdentityMatrix(m);
   m[0] = scale->x;
   m[5] = scale->y;
   m[10] = scale->z;
}

void setRotationMatrix (Matrix m, const Vec3D* eulerRads) {
   GLfloat cx = cos(eulerRads->x);
   GLfloat sx = sin(eulerRads->x);
   GLfloat cy = cos(eulerRads->y);
   GLfloat sy = sin(eulerRads->y);
   GLfloat cz = cos(eulerRads->z);
   GLfloat sz = sin(eulerRads->z);

   GLfloat cxsy = cx * sy;
   GLfloat sxsy = sx * sy;
   
   setIdentityMatrix(m);

   m[0] = cy * cz;
   m[4] = -cy * sz;
   m[8] = sy;
   m[1] = sxsy * cz + cx * sz;
   m[5] = -sxsy * sz + cx * cz;
   m[9] = -sx * cy;
   m[2] = -cxsy * cz + sx * sz;
   m[6] = cxsy * sz + sx * cz;
   m[10] = cx * cy;
}
   
void setPerspectiveMatrix (Matrix m, GLfloat fovy,
 	GLfloat aspect, GLfloat zNear, GLfloat zFar) {

   setIdentityMatrix(m);

   GLfloat d = 1.0 / tan((fovy * M_PI/180.0) / 2.0);

   m[0] = d / aspect;
   m[5] = d;
   m[10] = (zNear + zFar) / (zNear - zFar);
   m[14] = (2.0 * zNear * zFar) / (zNear - zFar);
   m[11] = -1.0;
}

Vec3D vecSubtract(Vec3D a, Vec3D b)
{
   Vec3D c = { (a.x - b.x), (a.y - b.y), (a.z - b.z) };
   return c;
} 

Vec3D vecAdd(Vec3D a, Vec3D b)
{
   Vec3D c = { (a.x + b.x), (a.y + b.y), (a.z + b.z) };
   return c;
}

Vec3D vecCross(Vec3D a, Vec3D b)
{
   Vec3D c;
   c.x = (a.y * b.z) - (a.z * b.y);
   c.y = (a.z * b.x) - (a.x * b.z);
   c.z = (a.x * b.y) - (a.y * b.x);
   return c;
}

Vec3D normalize(Vec3D a)
{
   double v = sqrt(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0));
   Vec3D c = { (a.x / v), (a.y / v), (a.z / v) };
   return c;
}
