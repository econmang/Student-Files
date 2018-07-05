/*
   glfuncs.h: shading example include file
   Created by: Kevin Sahr, 11/9/17
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

/*** type definitions ***/

typedef struct { 
   GLfloat x;
   GLfloat y; 
   GLfloat z; 
} Vec3D;

typedef struct {
  Vec3D position;
  Vec3D normal;
} Vertex;

// drawing function prototype
void drawIcosahedron (void);

#endif

