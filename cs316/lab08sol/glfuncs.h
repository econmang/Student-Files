/*
   glfuncs.h: cs316 lab 8 include file
   Created by: Kevin Sahr, 12/04/17
*/

#ifndef GLFUNCS_H
#define GLFUNCS_H

#include <stdio.h>

/*** GL include files ***/

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#define __gl_h_
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
#define MAX_VERTS 2000
#define MAX_TRIS  3500
#define MAX_NDXS  MAX_TRIS * 3
#define MAX_LINE  256

/*** type definitions ***/

typedef struct { 
   GLfloat x;
   GLfloat y; 
} Vec2D;

typedef struct { 
   GLfloat x;
   GLfloat y; 
   GLfloat z; 
} Vec3D;

typedef struct {
   GLfloat r;
   GLfloat g;
   GLfloat b;
   GLfloat a;
} RGBA;

typedef struct {
  Vec3D position;
  Vec3D normal;
} Vertex;

/*** function prototypes from lab 6 ***/
void loadObject (const char* fileName, Vertex* verts, GLuint* faces,
                 GLuint* numVerts, GLuint* numFaces);
void fileError (FILE* fp, const char* msg);
int getNextLine (char* nextLine, FILE* fp, int isEOFok);

/*** new function prototypes ***/
void normalize (Vec3D* v);
void vecCross (const Vec3D* v1, const Vec3D* v2, Vec3D* result);
void vecSub (const Vec3D* v1, const Vec3D* v2, Vec3D* result);
void vecAdd (const Vec3D* v1, const Vec3D* v2, Vec3D* result);
void vecScale (Vec3D* v, float scaleFac);
void getProp (FILE* fp, float prop[], char* msg);
void loadLight (const char* fileName);
void loadMaterial (const char* fileName);
void calculateNormals (Vertex verts[], int numVerts, 
                       const GLuint faces[], int numPtrs);

#endif

