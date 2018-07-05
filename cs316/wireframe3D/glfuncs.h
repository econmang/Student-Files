/*
   glfuncs.h: cs316 lab 6 include file
   Created by: Kevin Sahr, 11/9/17
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

/*** type definitions ***/

typedef struct { 
   GLfloat x;
   GLfloat y; 
   GLfloat z; 
} Vec3D;

#endif

