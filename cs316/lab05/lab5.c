/*
   lab3.c: main function and callbacks for cs316 lab 5
   Created by: Kevin Sahr, 10/31/17
*/

#include <stdlib.h>
#include <math.h>
#include "glfuncs.h" 
#include "matrix.h"
#include "shader.h" 

// global variables needed by displayCB
GLfloat left = -1.0;
GLfloat right = 1.0;
GLfloat bottom = -1.0;
GLfloat top = 1.0;

// the vertices to render
Vec2D verts[MAXVERTS];
int numVerts = 0;

// the drawing specifications
DrawSpec drawSpecs[MAXSPEC];
int numSpecs = 0;

// the handle of the shader program
GLuint shaderProgram;

static void displayCB (void)
{
   /* set the background color to opaque blue */
   glClearColor(0.0, 0.0, 1.0, 1.0);
   /* clear the viewport to the background color */
   glClear(GL_COLOR_BUFFER_BIT);

   // get the uniform handles

   GLint rotation = glGetUniformLocation(shaderProgram, "R");
   if (rotation == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint scale = glGetUniformLocation(shaderProgram, "S");
   if (scale == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint trans = glGetUniformLocation(shaderProgram, "T");
   if (trans == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint proj = glGetUniformLocation(shaderProgram, "projection");

   GLint fragColor = glGetUniformLocation(shaderProgram, "fragColor");
   if (fragColor == -1) fprintf(stderr, "ERROR: uniform not found\n");

   // draw with each of the drawing specifications
   int i;
   for (i = 0; i < numSpecs; i++) {

      DrawSpec* ds = &drawSpecs[i];

      Matrix M;

      setRotate2dMatrix(M,ds->rotRads);
      glUniformMatrix4fv(rotation, 1, GL_FALSE, M);

      setScale2dMatrix(M, ds->scale[0],ds->scale[1]);
      glUniformMatrix4fv(scale, 1, GL_FALSE, M);

      setTranslate2dMatrix(M, ds->trans[0],ds->trans[1]);
      glUniformMatrix4fv(trans, 1, GL_FALSE, M);

      setOrtho2dMatrix(M,left, right, bottom, top);
      glUniformMatrix4fv(proj, 1, GL_FALSE, M);

      glUniform4fv(fragColor, 1, ds->rgba);

      // now draw the primitive with the current values
      drawVerts(ds->drawType, verts, numVerts);
   }

   /* process all drawing commands */
   glFlush();
}

static void reshapeCB (int w, int h)
{
   // map new window bounds to current coordinate system
   glViewport(0, 0, w, h);
}

static void keyboardCB (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 'u':
	      top -= 0.03;
	      bottom -= 0.03;
	      glutPostRedisplay();
	      break;
      case 'd':
	      top += 0.03;
	      bottom += 0.03;
	      glutPostRedisplay();
	      break;
      case 'l':
	      left += 0.03;
	      right += 0.03;
	      glutPostRedisplay();
	      break;
      case 'r':
	      left -= 0.03;
	      right -= 0.03;
	      glutPostRedisplay();
	      break;
      case 'z':
	      left /= 1.03;
	      right /= 1.03;
	      top /= 1.03;
	      bottom /= 1.03;
	      glutPostRedisplay();
	      break;
      case 'Z':
	      left *= 1.03;
	      right *= 1.03;
	      top *= 1.03;
	      bottom *= 1.03;
	      glutPostRedisplay();
	      break;
      case 27: // escape key
         exit(0);
         break;
   }
}

int main (int argc, char* argv[]) {

   // check for correct number of cla's
   if (argc != 3)
   {
      fprintf(stderr, "usage: %s vertFile specFile\n", argv[0]);
      exit(1);
   }

   // read-in the vertices
   numVerts = readVertFile(argv[1], verts);
   if (numVerts <= 0) {
      fprintf(stderr, "ERROR: invalid vertex file.\n");
      exit(3);
   }

   // read-in the drawing specifications
   numSpecs = readSpecFile(argv[2], drawSpecs);
   if (numSpecs <= 0) {
      fprintf(stderr, "ERROR: invalid drawing specifications file.\n");
      exit(3);
   }

   // setup GLUT
   const int winSize = 500;
   const int winOffset = 100;

   /* set-up the window */
   glutInit(&argc, argv);
   glutInitWindowSize(winSize, winSize); // size in pixels
   glutInitWindowPosition(winOffset, winOffset); // upper left corner
   glutCreateWindow("Lab 5");
   glutInitDisplayMode(GLUT_DOUBLE);

   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   // create the shaders from the specified files
   const char* vertShaderFile = "matShader.vert";
   const char* fragShaderFile = "lab03.frag";
   shaderProgram = createShaderProgram(vertShaderFile, fragShaderFile);

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

