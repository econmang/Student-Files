/*
   lab2.c: main function and callbacks for cs316 lab 2
   Created by: Kevin Sahr, 10/5/17
*/

#include <stdlib.h>
#include <string.h>
#include "glfuncs.h" 

// global variables needed by displayCB

// which graphic primitive to render
GLuint drawType;

// the vertices to render
Vec2D verts[MAXVERTS];
int numVerts = 0;

static void displayCB (void)
{
   /* clear the viewport to the background color (default black) */
   glClear(GL_COLOR_BUFFER_BIT);

   /* draw with the foreground color (default white) */
   drawVerts(drawType, verts, numVerts);

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
      fprintf(stderr, "usage: %s drawType vertFile\n", argv[0]);
      exit(1);
   }

   // parse the graphics primitive type
   if (!strcmp(argv[1], "POINTS"))
      drawType = GL_POINTS;
   else if (!strcmp(argv[1], "LINES"))
      drawType = GL_LINE_STRIP;
   else if (!strcmp(argv[1], "POLY"))
      drawType = GL_LINE_LOOP;
   else {
      fprintf(stderr, 
         "ERROR: invalid graphics primitive \"%s\"\n",
         argv[1]);
      exit(2);
   }

   // read-in the vertices
   numVerts = readVertFile(argv[2], verts);
   if (numVerts <= 0) {
      fprintf(stderr, "ERROR: invalid vertex file.\n");
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

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

