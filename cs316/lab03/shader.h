/*
   shader.h: shader functions include file
   Created by: Kevin Sahr, 10/11/17
*/

#ifndef SHADER_H
#define SHADER_H

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

/*** function prototypes ***/

char* fileToString(const char *fileName);
GLuint createShaderProgram (const char* vertFileName, const char* fragFileName);

#endif

