/*
   matrix.h: simple 4x4 matrix library with 2D functions
   Created by: Kevin Sahr, 10/31/17
*/

#include "glfuncs.h" 

#define MATRIX_DIM 4
typedef GLfloat Matrix[MATRIX_DIM * MATRIX_DIM];

// function prototypes
void printMatrix (Matrix m);
void setIdentityMatrix (Matrix m);
void setScaleMatrix (Matrix m, const Vec3D* eulerRads);
void setTranslateMatrix (Matrix m, const Vec3D* trans);
void setRotationMatrix (Matrix m, const Vec3D* eulerRads);
void setPerspectiveMatrix (Matrix m, GLfloat fovy,
        GLfloat aspect, GLfloat zNear, GLfloat zFar);

// 2D matrices
void setScale2dMatrix (Matrix m, GLfloat sx, GLfloat sy);
void setRotate2dMatrix (Matrix m, GLfloat thetaRads);
void setTranslate2dMatrix (Matrix m, GLfloat tx, GLfloat ty);
void setOrtho2dMatrix (Matrix m, GLfloat left, GLfloat right,
		GLfloat bottom, GLfloat top);
