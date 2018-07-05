/*
   lab3.c: main function and callbacks for cs316 lab 3
   Created by: Kevin Sahr, 10/11/17
*/

#include <stdlib.h>
#include <string.h>
#include "glfuncs.h"
#include "shader.h"

// global variables needed by displayCB

// the handle of the shader program
GLuint shaderProgram;
// which graphic primitive to render
GLuint drawType;

// the vertices to render
Vec2D verts[MAXVERTS];
int numVerts = 0;

// the specs of drawing
SpecStruct specs[MAXSPECS];
int numSpecs = 0;
int check = 0;

static void displayCB (void)
{
   /* clear the viewport to the background color (set to blue) */
   glClearColor(0.0, 0.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);

   // get the uniform for rotation angle
   GLint theta = glGetUniformLocation(shaderProgram, "theta");
   if (theta == -1) fprintf(stderr, "ERROR: uniform theta not found\n");
   
   // get the uniforms that represents the scaling factor
   GLint xscale = glGetUniformLocation(shaderProgram, "xscale");
   GLint yscale = glGetUniformLocation(shaderProgram, "yscale");
   if (xscale == -1 || yscale == -1) fprintf(stderr, "ERROR: uniform scale not found\n");

   //get translation factors
   GLint xtrans = glGetUniformLocation(shaderProgram, "xtrans");
   GLint ytrans = glGetUniformLocation(shaderProgram, "ytrans");
   if (xtrans == -1 || ytrans == -1) fprintf(stderr, "ERROR: uniform tranlsation not found\n");

   GLint fragColor = glGetUniformLocation(shaderProgram, "fragColor");
   if (fragColor == -1) fprintf(stderr, "ERROR: uniform not found\n");

   while (check < numSpecs){
      drawType = specs[check].drawType;

      glUniform1f(theta,specs[check].rotAng);
      glUniform1f(xscale,specs[check].scalx);
      glUniform1f(yscale,specs[check].scaly);
      glUniform1f(xtrans,specs[check].tranx);
      glUniform1f(ytrans,specs[check].trany);

      GLfloat col[] = {specs[check].R,specs[check].G,
         specs[check].B,specs[check].A};
      glUniform4fv(fragColor, 1, col);

      drawVerts(drawType, verts, numVerts);
      check++;
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

   // read-in the specifications
   numSpecs = readSpecs(argv[2], specs);
   if (numSpecs <= 0) {
      fprintf(stderr, "ERROR: invalid specifications file.\n");
      exit(3);
   }

   // setup GLUT
   const int winSize = 500;
   const int winOffset = 100;

   /* set-up the window */
   glutInit(&argc, argv);
   glutInitWindowSize(winSize, winSize); // size in pixels
   glutInitWindowPosition(winOffset, winOffset); // upper left corner
   glutCreateWindow("Lab 2");

   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   /* create the shaders */
   shaderProgram = createShaderProgram("labThree.vert","labThree.frag");
   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

