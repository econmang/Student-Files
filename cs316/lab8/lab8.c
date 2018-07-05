/*
   lab6.c: cs316 Lab 6
   Created by: Kevin Sahr
   November 9, 2017
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
Vec3D pVerts[MAX_VERTS];
Vertex verts[MAX_VERTS];
GLuint faces[MAX_NDXS];
Vertex facesNorms[MAX_NDXS / 3];

//light values
Vec3D lPos;
RGBA lAmb, lDiff, lSpec, emis;
K k;
GLuint n;

GLuint numVerts = 0, numFaces = 0;
RGBA col = { 1.0, 1.0, 1.0, 1.0 };

//const int numVerts = 60;

void calcNormals()
{
   int i, j, numAdj;
   Vec3D norm, total;
   Vec3D v1, v2, v3;

   for(i = 0; i < numVerts; i++)
   {
      verts[i].position = pVerts[i];
      verts[i].normal = verts[i].position;
   }
    
   //calculate face normals
   for(i = 0; i < numFaces; i++)
   {
      facesNorms[i / 3].position.x = faces[i];
      v1 = verts[(int)(facesNorms[i / 3].position.x)].position;
      i++;
      facesNorms[i / 3].position.y = faces[i];
      v2 = verts[(int)facesNorms[i / 3].position.y].position;
      i++;
      facesNorms[i / 3].position.z = faces[i];
      v3 = verts[(int)facesNorms[i / 3].position.z].position;

      norm = normalize(vecCross(vecSubtract(v2, v1), vecSubtract(v3, v1)));
      facesNorms[i / 3].normal = norm;


   }

   //calculate vector normals
   for(i = 0; i < numVerts; i++)
   {
      total.x = 0;
      total.y = 0;
      total.z = 0;
      numAdj = 0;

      for(j = 0; j < numFaces / 3; j++)
      {
         if(facesNorms[j].position.x == i || facesNorms[j].position.y == i || facesNorms[j].position.z == i)
         {
            total = vecAdd(total, facesNorms[j].normal);
            numAdj++;
         }
      }
      total.x = total.x / numAdj;
      total.y = total.y / numAdj;
      total.z = total.z / numAdj;
      verts[i].normal = normalize(total);
   }
}

void drawObject (void)
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
   glVertexAttribPointer(normal, 4, GL_FLOAT, GL_FALSE,
        sizeof(Vertex),(GLvoid*)sizeof(Vec3D));
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
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   /* setup vertex transformation matrices */

   GLint view = glGetUniformLocation(shaderProgram, "view");
   if (view == -1) fprintf(stderr, "ERROR: uniform not found\n");

   GLint proj = glGetUniformLocation(shaderProgram, "proj");
   if (proj == -1) fprintf(stderr, "ERROR: uniform not found\n");

   // create a matrix
   Matrix M;

   /* setup model transformation matrices */
   GLint scale = glGetUniformLocation(shaderProgram, "scale");
   if (scale == -1) fprintf(stderr, "ERROR: uniform not found\n");

   Vec3D scaleVec = { scaleFactor, scaleFactor, scaleFactor };
   setScaleMatrix (M, &scaleVec);
   glUniformMatrix4fv(scale, 1, GL_FALSE, M);

   GLint rotate = glGetUniformLocation(shaderProgram, "rotate");
   if (rotate == -1) fprintf(stderr, "ERROR: uniform not found\n");

   setRotationMatrix (M, &eulerRads);
   glUniformMatrix4fv(rotate, 1, GL_FALSE, M);

   GLint lPosition = glGetUniformLocation(shaderProgram, "lightPosition");
   if (lPosition == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform4f(lPosition, lPos.x, lPos.y, lPos.z, 1.0);

   GLint lDiffuse = glGetUniformLocation(shaderProgram, "lightDiffuse");
   if (lDiffuse == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform3f(lDiffuse, lDiff.r, lDiff.g, lDiff.b);

   GLint lSpecular = glGetUniformLocation(shaderProgram, "lightSpecular");
   if (lSpecular == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform3f(lSpecular, lSpec.r, lSpec.g, lSpec.b);

   GLint lAmbient = glGetUniformLocation(shaderProgram, "lightAmbient");
   if (lAmbient == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform3f(lAmbient, lAmb.r, lAmb.g, lAmb.b);

   GLint lemissive = glGetUniformLocation(shaderProgram, "emissive");
   if (lemissive == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform3f(lemissive, emis.r, emis.g, emis.b);

   GLint ka = glGetUniformLocation(shaderProgram, "ka");
   if (ka == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(ka, k.a);

   GLint kd = glGetUniformLocation(shaderProgram, "kd");
   if (kd == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(kd, k.d);

   GLint ks = glGetUniformLocation(shaderProgram, "ks");
   if (ks == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(ks, k.s);

   GLint ns = glGetUniformLocation(shaderProgram, "ns");
   if (ns == -1) fprintf(stderr, "ERROR: uniform not found\n");
   glUniform1f(ns, (float)n);



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

   /* set-up the window */
   glutInit(&argc, argv);
   glutInitWindowSize(winSize, winSize); // size in pixels
   glutInitWindowPosition(winOffset, winOffset); // upper left corner
   glutCreateWindow("wireframe");
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   /* register the callbacks */

   glutDisplayFunc(displayCB);
   glutReshapeFunc(reshapeCB);
   glutKeyboardFunc(keyboardCB);

   // create the shaders from the specified files
   const char* vertShaderFile = "phong.vert";
   const char* fragShaderFile = "phong.frag";
   shaderProgram = createShaderProgram(vertShaderFile, fragShaderFile);

   // load the object to render
   loadObject(argv[1], pVerts, faces, &numVerts, &numFaces, &col);
   loadLight(argv[2], &lAmb, &lDiff, &lSpec, &lPos);
   loadMat(argv[3], &emis, &k, &n);

   calcNormals();

   // turn-on z-buffering and back face culling
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glDepthMask(GL_TRUE);

   /* enter the control loop */
   glutMainLoop();

   return 0;

} // int main

