/*
   lab8.c: cs316 Lab 8
   Created by: Kevin Sahr
   December 4, 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "glfuncs.h"
#include "shader.h"
#include "matrix.h"

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
static Vertex verts[MAX_VERTS];
static GLuint faces [MAX_NDXS];
GLuint numVerts = 0, numFaces = 0;

static void drawObject (void)
{
   glPolygonMode(GL_FRONT, GL_FILL);

   GLint position = glGetAttribLocation(shaderProgram, "position");
   if (position == -1) fprintf(stderr, "ERROR: varying not found\n");
   GLint normal = glGetAttribLocation(shaderProgram, "normal");
   if (normal == -1) fprintf(stderr, "ERROR: varying not found\n");

   // identifiers for the vertex array object and vertex buffer
   // objects
   GLuint vao, vbo, ebo;

   // generate a single VAO 
   glGenVertexArrays(1, &vao);
   // bound VAO will store connections between VBOs and attributes
   glBindVertexArray(vao); // make it the active VAO
 
   // generate and bind the VBO to store the vertex data
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo); 
   // initialize VBO, allocate memory, fill it with data
   glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

   // specify vertex position attribute
   glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(position);

   // specify vertex normal attribute
   glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                         (GLvoid*)sizeof(Vec3D));
   glEnableVertexAttribArray(normal);

   // create new buffer that will be used to store indices
   glGenBuffers(1, &ebo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); 
   // initialize index buffer, allocate memory, fill it with data
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

   // now do the drawing
   // bind the index buffer
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   // indexed draw call
   glDrawElements(GL_TRIANGLES, numFaces, GL_UNSIGNED_INT, NULL);
}

static void displayCB (void)
{
   /* clear the viewport */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // create a matrix
   Matrix M;

   /* setup model transformation matrices */
   GLint scale = glGetUniformLocation(shaderProgram, "scale");
   if (scale == -1) fprintf(stderr, "ERROR: uniform scale not found\n");
   Vec3D scaleVec = { scaleFactor, scaleFactor, scaleFactor };
   setScaleMatrix (M, &scaleVec);
   glUniformMatrix4fv(scale, 1, GL_FALSE, M);

   GLint rotate = glGetUniformLocation(shaderProgram, "rotate");
   if (rotate == -1) fprintf(stderr, "ERROR: uniform not found\n");
   setRotationMatrix (M, &eulerRads);
   glUniformMatrix4fv(rotate, 1, GL_FALSE, M);

   // the view matrix should translate the eye point to the origin
   GLint view = glGetUniformLocation(shaderProgram, "view");
   if (view == -1) fprintf(stderr, "ERROR: uniform view not found\n");
   Vec3D viewTrans = eye;
   viewTrans.x *= -1.0;
   viewTrans.y *= -1.0;
   viewTrans.z *= -1.0;
   setTranslateMatrix (M, &viewTrans);
   glUniformMatrix4fv(view, 1, GL_FALSE, M);

   // set the uniform projection matrix to a perspective projection
   GLint proj = glGetUniformLocation(shaderProgram, "proj");
   if (proj == -1) fprintf(stderr, "ERROR: uniform proj not found\n");
   setPerspectiveMatrix(M, 60, 1.0, 0.1, 6.0);
   glUniformMatrix4fv(proj, 1, GL_FALSE, M);

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
      fprintf(stderr, "usage: %s objectFileName lightFileName materialFileName\n", argv[0]);
      exit(1);
   }

   // setup GLUT
   const int winSize = 500;
   const int winOffset = 100;

   /* set-up the window */
   glutInit(&argc, argv);
   glutInitWindowSize(winSize, winSize); // size in pixels
   glutInitWindowPosition(winOffset, winOffset); // upper left corner
   glutCreateWindow("Lab 8");
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   // create the shaders from the specified files
   const char* vertShaderFile = "lab8.vert";
   const char* fragShaderFile = "lab8.frag";
   shaderProgram = createShaderProgram(vertShaderFile, fragShaderFile);

   // load the scene to render
   loadObject(argv[1], verts, faces, &numVerts, &numFaces);
   loadLight(argv[2]);
   loadMaterial(argv[3]);
   calculateNormals (verts, numVerts, faces, numFaces);

   // turn-on z-buffering and back face culling
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glDepthMask(GL_TRUE);

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

