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
