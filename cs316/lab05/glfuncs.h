/*
   glfuncs.h: cs316 lab 3 include file
   Created by: Kevin Sahr, 10/5/17
*/

#ifndef GLFUNCS_H
#define GLFUNCS_H

#include <stdio.h>

/*** GL include files ***/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <Glut/glut.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

/*** constants ***/
#define MAXVERTS 1000
#define MAXLINE  256
#define MAXSPEC   500

/*** type definitions ***/

typedef struct { 
   GLfloat x;
   GLfloat y; 
} Vec2D;

typedef struct { 
   GLuint drawType; // graphics primitive
   GLfloat rotRads;   // ccw rotation angle in radians
   GLfloat scale[2];  // scaling vector
   GLfloat trans[2];  // translation vector
   GLfloat rgba[4];   // color
} DrawSpec;

/*** function prototypes ***/

void drawVerts(GLuint drawType, const Vec2D verts[], int numVerts);
void drawPoints (const Vec2D pts[], int numPts);
void drawPolyline (const Vec2D pts[], int numPts);
void drawPolygon (const Vec2D pts[], int numPts);
int readOneVert (FILE* inFile, Vec2D* v);
int readVertFile (const char* fileName, Vec2D* verts);
int readOneSpec (FILE* inFile, DrawSpec* d);
int readSpecFile (const char* fileName, DrawSpec* specs);

#endif

