/*
   phong.c: cs316 phong shading with Phong lighting example
   Created by: Kevin Sahr
*/

#include <stdio.h>
#include <stdlib.h>
#include "glfuncs.h"
#include "shader.h"
#include "matrix.h"

// eye movement constant
const GLfloat EYE_INCREMENT = 0.1;
// assume eye starts 3.0 units along z-axis from the world space origin
Vec3D eye = { 0.0, 0.0, 3.0 };
// rotation constant
const GLfloat ANG_INCREMENT = 0.1;
GLfloat rotRads = 0.0;

// the handle of the shader program
GLuint shaderProgram;

static void displayCB (void)
{
   /* clear the viewport */
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   /* setup vertex transformation matrices */

   GLint model = glGetUniformLocation(shaderProgram, "model");
   if (model == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint view = glGetUniformLocation(shaderProgram, "view");
   if (view == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint proj = glGetUniformLocation(shaderProgram, "proj");
   if (proj == -1) fprintf(stderr, "ERROR: uniform not found\n");

   // create a matrix
   Matrix M;

   // the modeling matrix only does rotation about x-axes
   Vec3D euler = { rotRads, 0.0, 0.0 };
   setRotationMatrix (M, &euler);
   glUniformMatrix4fv(model, 1, GL_FALSE, M);

   // the view matrix should translate the eye point to the origin
   Vec3D viewTrans = eye;
   viewTrans.x *= -1.0;
   viewTrans.y *= -1.0;
   viewTrans.z *= -1.0;
   setTranslateMatrix (M, &viewTrans);
   glUniformMatrix4fv(view, 1, GL_FALSE, M);

   // set the uniform projection matrix to a perspective projection
   setPerspectiveMatrix(M, 60, 1.0, 0.1, 5.0);
   glUniformMatrix4fv(proj, 1, GL_FALSE, M);

   /* now draw the icosahedron */
   drawIcosahedron();

   /* swap the buffers */
   glutSwapBuffers();
}

static void reshapeCB (int w, int h)
{
   glViewport(0, 0, w, h);
}

static void keyboardCB (unsigned char key, int x, int y)
{
   switch (key)
   {
      case 'f': // move eye towards tetrahedron
         eye.z -= EYE_INCREMENT;
         break;

      case 'b': // move eye away from tetrahedron
         eye.z += EYE_INCREMENT;
         break;

      case 'l': // move eye left
         eye.x -= EYE_INCREMENT;
         break;

      case 'r': // move eye right
         eye.x += EYE_INCREMENT;
         break;

      case 'x':
         rotRads += ANG_INCREMENT;
         break;

      case 'X':
         rotRads -= ANG_INCREMENT;
         break;

      case 27: // escape key
         exit(0);
         break;
   }

   glutPostRedisplay();
}

int main (int argc, char* argv[])
{
   // setup GLUT
   const int winSize = 500;
   const int winOffset = 100;

   /* set-up the window */
   glutInit(&argc, argv);
   glutInitWindowSize(winSize, winSize); // size in pixels
   glutInitWindowPosition(winOffset, winOffset); // upper left corner
   glutCreateWindow("phong shading");
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   // create the shaders from the specified files
   const char* vertShaderFile = "phong.vert";
   const char* fragShaderFile = "phong.frag";
   shaderProgram = createShaderProgram(vertShaderFile, fragShaderFile);

   // turn-on z-buffering and back face culling
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glDepthMask(GL_TRUE);

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

