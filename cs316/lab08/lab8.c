/*
   lab8.c: cs316 Lab 8
   Created by: Kevin Sahr
   November 9, 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "glfuncs.h"
#include "shader.h"
#include "matrix.h"

Vec3D lightPos;
RGBA amb;
RGBA diff;
RGBA spec;

RGBA em;
GLfloat* ka;
GLfloat* kd;
GLfloat* ks;
GLfloat* ns;


// eye movement constant
const GLfloat EYE_INCREMENT = 0.1;
// assume eye starts 4.0 units along z-axis from the world space origin
Vec3D eye = { 0.0, 0.0, 4.0 };

const GLfloat ANG_INCREMENT = 0.1;
Vec3D eulerRads = { 0.0, 0.0, 0.0 };

const float SCALE_INCREMENT = 1.03;
GLfloat scaleFactor = 1.0;

// the handle of the shader program
GLuint shaderProgram;

// the object definition
Vec3D verts[MAX_VERTS];
GLuint faces[MAX_NDXS];
GLuint numVerts = 0, numFaces = 0;
RGBA col = { 1.0, 1.0, 1.0, 1.0 };

static void drawObject (void)
{
   glPolygonMode(GL_FRONT, GL_FILL);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, verts);

   glDrawElements(GL_TRIANGLES, numFaces, GL_UNSIGNED_INT, faces);
}

static void displayCB (void)
{
   /* clear the viewport */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // create a matrix
   Matrix M;

   /* setup model transformation matrices */
   GLint rotate = glGetUniformLocation(shaderProgram, "model");
   if (rotate == -1) fprintf(stderr, "ERROR: uniform not found\n");
   setRotationMatrix (M, &eulerRads);
   glUniformMatrix4fv(rotate, 1, GL_FALSE, M);

   // the view matrix should translate the eye point to the origin
   GLint view = glGetUniformLocation(shaderProgram, "view");
   if (view == -1) fprintf(stderr, "ERROR: uniform not found\n");
   Vec3D viewTrans = eye;
   viewTrans.x *= -1.0;
   viewTrans.y *= -1.0;
   viewTrans.z *= -1.0;
   setTranslateMatrix (M, &viewTrans);
   glUniformMatrix4fv(view, 1, GL_FALSE, M);

   // set the uniform projection matrix to a perspective projection
   GLint proj = glGetUniformLocation(shaderProgram, "proj");
   if (proj == -1) fprintf(stderr, "ERROR: uniform not found\n");
   setPerspectiveMatrix(M, 60, 1.0, 0.1, 6.0);
   glUniformMatrix4fv(proj, 1, GL_FALSE, M);

   GLint lpos = glGetUniformLocation(shaderProgram, "lightPosition");
   if (lpos == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform3f(lpos,lightPos.x,lightPos.y,lightPos.z);

   GLint emiss = glGetUniformLocation(shaderProgram, "emissive");
   if (emiss == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform4f(emiss, em.r,em.g,em.b,em.a);

   GLint lightdiff = glGetUniformLocation(shaderProgram, "lightDiffuse");
   if (lightdiff == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform4f(lightdiff, diff.r, diff.g, diff.g, diff.a);

   GLint lightspec = glGetUniformLocation(shaderProgram, "lightSpecular");
   if (lightspec == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform4f(lightspec, spec.r, spec.g, spec.b, spec.a);

   GLint lightamb = glGetUniformLocation(shaderProgram, "lightAmbient");
   if (lightamb == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform4f(lightamb, amb.r, amb.g, amb.b, amb.a);

   GLint constka = glGetUniformLocation(shaderProgram, "ka");
   if (constka == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(constka, *ka);

   GLint constkd = glGetUniformLocation(shaderProgram, "kd");
   if (constkd == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(constkd, *kd);

   GLint constks = glGetUniformLocation(shaderProgram, "ks");
   if (constks == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(constks, *ks);

   GLint constns = glGetUniformLocation(shaderProgram, "ns");
   if (constns == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(constns, *ns);

   /* now draw the object */
   drawObject();

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

      case 'u': // move eye up
         eye.y += EYE_INCREMENT;
         break;

      case 'd': // move eye down
         eye.y -= EYE_INCREMENT;
         break;

      case '+': // scale up
         scaleFactor *= SCALE_INCREMENT;
         break;

      case '-': // scale up
         scaleFactor /= SCALE_INCREMENT;
         break;

      case 'x':
         eulerRads.x += ANG_INCREMENT;
         break;

      case 'X':
         eulerRads.x -= ANG_INCREMENT;
         break;

      case 'y':
         eulerRads.y += ANG_INCREMENT;
         break;

      case 'Y':
         eulerRads.y -= ANG_INCREMENT;
         break;

      case 'z':
         eulerRads.z += ANG_INCREMENT;
         break;

      case 'Z':
         eulerRads.z -= ANG_INCREMENT;
         break;

      case 27: // escape key
         exit(0);
         break;
   }

   glutPostRedisplay();
}

int main (int argc, char* argv[])
{
   if (argc != 4)
   {
      fprintf(stderr, "usage: %s objectFileName lightPropFileName materialPropFileName\n", argv[0]);
      exit(1);
   }

   // setup GLUT
   const int winSize = 500;
   const int winOffset = 100;
   printf("Setting up windown\n\n");
   /* set-up the window */
   glutInit(&argc, argv);
   glutInitWindowSize(winSize, winSize); // size in pixels
   glutInitWindowPosition(winOffset, winOffset); // upper left corner
   glutCreateWindow("wireframe");
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

   printf("Window setup\n\n");
   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   printf("Creating shader program\n\n");

   // create the shaders from the specified files
   const char* vertShaderFile = "phong.vert";
   const char* fragShaderFile = "phong.frag";
   shaderProgram = createShaderProgram(vertShaderFile, fragShaderFile);

   printf("Shader program created\n\n");

   printf("Starting face culling and z-buffer\n\n");

   //turn on z-buffering and back face culling
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glDepthMask(GL_TRUE);

   printf("loading object\n\n");

   // load the object to render
   loadObject(argv[1], verts, faces, &numVerts, &numFaces, &col);
   printf("object loaded\n\n");
   printf("loading light specs\n\n");
   loadLight(argv[2], lightPos, amb, diff, spec);
   printf("loaded light specs \n\n");
   printf("Loading material specs\n\n");
   loadMaterial(argv[3], em, ka, kd, ks, ns);
   printf("Material specs loaded\n\n");

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

