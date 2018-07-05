/*
   glfuncs.h: cs316 lab 6 include file
   Created by: Kevin Sahr, 11/15/17
*/

#ifndef GLFUNCS_H
#define GLFUNCS_H

#include <stdio.h>
#include <math.h>

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

/*** function prototypes ***/

void loadObject (const char* fileName, Vec3D* verts, GLuint* faces,
                 GLuint* numVerts, GLuint* numFaces, RGBA* col);

void loadLight(const char* fileName, Vec3D lightpos, RGBA amb, RGBA diff, RGBA spec);
void loadMaterial(const char* fileName, RGBA em, GLfloat* ka, GLfloat* kd, GLfloat* ks, GLfloat* ns);

void fileError (FILE* fp, const char* msg);
int getNextLine (char* nextLine, FILE* fp, int isEOFok);

Vec3D crossProduct(Vec3D A, Vec3D B);
Vec3D normalize(Vec3D vector);
Vec3D vecAddition(Vec3D A, Vec3D B);
Vec3D vecSubtract(Vec3D A, Vec3D B);


#endif
