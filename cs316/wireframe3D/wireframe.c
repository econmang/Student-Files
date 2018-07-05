/*
   wireframe.c: cs316 3D wireframe drawing example
   Created by: Kevin Sahr
*/

#include <stdio.h>
#include <stdlib.h>
#include "glfuncs.h"
#include "shader.h"
#include "matrix.h"

// eye movement constant
const GLfloat EYE_INCREMENT = 0.1;

// assume eye starts 3.5 units along z-axis from the world space origin
Vec3D eye = { 0.0, 0.0, 3.5 };

// the handle of the shader program
GLuint shaderProgram;

// the tetrahedron vertex list
const Vec3D verts[] = {
   { 0.5,  0.5,  0.5}, /* vert 0 */
   { 0.5, -0.5, -0.5}, /* vert 1 */
   {-0.5, -0.5,  0.5}, /* vert 2 */
   {-0.5,  0.5, -0.5}  /* vert 3 */
};

// pointer to vertex list
const GLuint faces[] = {
     1, 2, 3,
     0, 3, 2,
     0, 1, 3,
     0, 2, 1
};

const int numVerts = 12;

static void drawTetrahedron (void)
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, verts);

   glDrawElements(GL_TRIANGLES, numVerts, GL_UNSIGNED_INT, faces);
}

static void displayCB (void)
{
   /* clear the viewport */
   glClear(GL_COLOR_BUFFER_BIT);

   /* setup vertex transformation matrices */

   GLint view = glGetUniformLocation(shaderProgram, "view");
   if (view == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint proj = glGetUniformLocation(shaderProgram, "proj");
   if (proj == -1) fprintf(stderr, "ERROR: uniform not found\n");

   // create a matrix
   Matrix M;

   // the view matrix should translate the eye point to the origin
   Vec3D viewTrans = eye;
   viewTrans.x *= -1.0;
   viewTrans.y *= -1.0;
   viewTrans.z *= -1.0;
   setTranslateMatrix (M, &viewTrans);
   glUniformMatrix4fv(view, 1, GL_FALSE, M);

   // set the uniform projection matrix to a perspective projection
   setPerspectiveMatrix(M, 60, 1.0, 2.0, 5.0);
   //setIdentityMatrix(M);
   glUniformMatrix4fv(proj, 1, GL_FALSE, M);

   /* now draw the tetrahedron */
   drawTetrahedron();

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
         glutPostRedisplay();
         break;

      case 'b': // move eye away from tetrahedron
         eye.z += EYE_INCREMENT;
         glutPostRedisplay();
         break;

      case 'l': // move eye left
         eye.x -= EYE_INCREMENT;
         glutPostRedisplay();
         break;

      case 'r': // move eye right
         eye.x += EYE_INCREMENT;
         glutPostRedisplay();
         break;

      case 27: // escape key
         exit(0);
         break;
   }
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
   glutCreateWindow("wireframe");
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   // create the shaders from the specified files
   const char* vertShaderFile = "proj.vert";
   const char* fragShaderFile = "white.frag";
   shaderProgram = createShaderProgram(vertShaderFile, fragShaderFile);

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

