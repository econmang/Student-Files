/*
   glfuncs.c: function definitions for cs316 lab 8
   Created by: Kevin Sahr, 12/04/17
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "glfuncs.h" 

extern GLuint shaderProgram;

void loadObject (const char* fileName, Vertex* verts, GLuint* faces, 
                 GLuint* numVerts, GLuint* numFaces)
{
   FILE* fp;
   int retVal, i, n, v1, v2, v3;
   char nextLine[MAX_LINE];

   /* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: file %s not found\n", fileName);
      exit(1);
   }

   /* get the color; this is not used by lab 8 */
   RGBA col;
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in color\n");
      exit(2);
   }

   /* get the number of vertices */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%d", numVerts) != 1)
   {
      fprintf(stderr, "ERROR: invalid file format in # verts\n");
      exit(2);
   }

   /* get the vertices */
   for (i = 0; i < *numVerts; i++)
   {
      getNextLine(nextLine, fp, 0);
      if (sscanf(nextLine, "%d %f %f %f", &n, &(verts[i].position.x), &(verts[i].position.y),
               &(verts[i].position.z)) != 4) {
         fprintf(stderr, "ERROR: invalid file format in verts\n");
         exit(2);
      } else if (i != n) {
         fprintf(stderr, "ERROR: invalid vertex sequence number\n");
         exit(2);
      }
   }

   /* get the pointers-to-vertices */
   *numFaces = 0;
   while (1)
   {
      if (getNextLine(nextLine, fp, 1) == EOF)
         break;

      if ((*numFaces + 2) >= MAX_NDXS)
      {
         fprintf(stderr, "ERROR: too many indexes in file.\n");
         exit(2);
      }
      
      retVal = sscanf(nextLine, "%d %d %d", &v1, &v2, &v3);
      if (retVal == EOF) 
         return;
      else if (retVal != 3) {
         fprintf(stderr, "ERROR: invalid vertex pointers.\n");
         exit(2);
      } else if (v1 < 0 || v1 >= *numVerts || v2 < 0 || v2 >= *numVerts ||
          v3 < 0 || v3 >= *numVerts) {
         fprintf(stderr, "ERROR: vertex pointer out-of-bounds.\n");
         exit(2);
      }

      faces[(*numFaces)++] = v1;
      faces[(*numFaces)++] = v2;
      faces[(*numFaces)++] = v3;
   } 

   fclose(fp);
}

void fileError (FILE* fp, const char* msg)
{
   fprintf(stderr, "ERROR: %s\n", msg);
   fclose(fp);
   exit(2);
}

int getNextLine (char* nextLine, FILE* fp, int isEOFok)
{
   if (!fgets(nextLine, MAX_LINE, fp)) {
      if (feof(fp)) // check for EOF
      {
         if (isEOFok)
            return EOF; // successful completion
         else
            fileError(fp, "unexpected EOF.");
      }
      else
         fileError(fp, "problem reading file.");
   }

   return 0;
}

/**************************************************************************/
void normalize (Vec3D* v)
{
   double mag = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

   if (mag > 0.0)
   {
      v->x /= mag;
      v->y /= mag;
      v->z /= mag;
   }

} /* void normalize */

/**************************************************************************/
void vecCross (const Vec3D* v1, const Vec3D* v2, Vec3D* result)
{
   result->x = v1->y * v2->z - v1->z * v2->y;
   result->y = v1->z * v2->x - v1->x * v2->z;
   result->z = v1->x * v2->y - v1->y * v2->x;

} /* void vecCross */

/**************************************************************************/
void vecSub (const Vec3D* v1, const Vec3D* v2, Vec3D* result)
{
   result->x = v1->x - v2->x;
   result->y = v1->y - v2->y;
   result->z = v1->z - v2->z;

} /* void vecSub */

/**************************************************************************/
void vecAdd (const Vec3D* v1, const Vec3D* v2, Vec3D* result)
{
   result->x = v1->x + v2->x;
   result->y = v1->y + v2->y;
   result->z = v1->z + v2->z;

} /* void vecAdd */

/**************************************************************************/
void vecScale (Vec3D* v, float scaleFac)
{
   v->x *= scaleFac;
   v->y *= scaleFac;
   v->z *= scaleFac;
}

/**************************************************************************/
void getProp (FILE* fp, float prop[], char* msg)
{
   char nextLine[MAX_LINE + 1];
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &prop[0], &prop[1], &prop[2],
                                 &prop[3]) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in %s.\n", msg);
      exit(2);
   }
}

/**************************************************************************/
void loadLight (const char* fileName)
{
   GLfloat prop[4];
   FILE* fp;

   /* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: %s not found\n", fileName);
      exit(1);
   }

   /*** get the lighting properties ***/

   // first read and set the light position
   char nextLine[MAX_LINE + 1];
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f", &prop[0], &prop[1], &prop[2]) != 3)
   {
      fprintf(stderr, "ERROR: invalid file format in %s.\n", fileName);
      exit(2);
   }
   prop[3] = 1.0;

   GLint propUniform = glGetUniformLocation(shaderProgram, "lightPosition");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform lightPosition not found\n");
   glUniform3fv(propUniform, 1, prop);

   // ambient
   getProp(fp, prop, "ambient component");
   propUniform = glGetUniformLocation(shaderProgram, "lightAmbient");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform lightAmbient not found\n");
   glUniform3fv(propUniform, 1, prop);

   // diffuse
   getProp(fp, prop, "diffuse component");
   propUniform = glGetUniformLocation(shaderProgram, "lightDiffuse");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform lightDiffuse not found\n");
   glUniform3fv(propUniform, 1, prop);

   // specular
   getProp(fp, prop, "specular component");
   propUniform = glGetUniformLocation(shaderProgram, "lightSpecular");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform lightSpecular not found\n");
   glUniform3fv(propUniform, 1, prop);

   fclose(fp);
}

/**************************************************************************/
void loadMaterial (const char* fileName)
{
   GLfloat prop[4];
   FILE* fp;

   /* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: %s not found\n", fileName);
      exit(1);
   }

   /*** get the material properties ***/

   // emmissive
   getProp(fp, prop, "emissive component");
   GLint propUniform = glGetUniformLocation(shaderProgram, "emissive");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform emissive not found\n");
   glUniform3fv(propUniform, 1, prop);

   // coefficients
   GLfloat ka, kd, ks;
   char nextLine[MAX_LINE + 1];
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f", &ka, &kd, &ks) != 3)
   {
      fprintf(stderr, "ERROR: invalid file format in %s.\n", fileName);
      exit(2);
   }

   propUniform = glGetUniformLocation(shaderProgram, "ka");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform ka not found\n");
   glUniform1f(propUniform, ka);
   propUniform = glGetUniformLocation(shaderProgram, "kd");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform kd not found\n");
   glUniform1f(propUniform, kd);
   propUniform = glGetUniformLocation(shaderProgram, "ks");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform ks not found\n");
   glUniform1f(propUniform, ks);

   GLfloat ns;
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f", &ns) != 1)
   {
      fprintf(stderr, "ERROR: invalid file format in shininess\n");
      exit(2);
   }
   propUniform = glGetUniformLocation(shaderProgram, "ns");
   if (propUniform == -1) fprintf(stderr, "ERROR: uniform ns not found\n");
   glUniform1f(propUniform, ns);

   fclose(fp);
}

/**************************************************************************/
void calculateNormals (Vertex verts[], int numVerts, 
                       const GLuint faces[], int numPtrs)
{
   int numTris = numPtrs / 3;

   /* initialize the vertex normals and face counters for each vertex */
   int facesPerVert[MAX_VERTS];
   int i;
   for (i = 0; i < numVerts; i++)
   {
      verts[i].normal.x = 0.0;
      verts[i].normal.y = 0.0;
      verts[i].normal.z = 0.0;

      facesPerVert[i] = 0;
   }

   /* calculate the normals for each triangle; keep a running total of
      the face normals adjacent to each vertex */
   int pNdx = 0;
   for (i = 0; i < numTris; i++)
   {
      /* some temp variables */
      int p1 = faces[pNdx];
      int p2 = faces[pNdx + 1];
      int p3 = faces[pNdx + 2];

      /* calculate the triangle normal */
      Vec3D v1, v2, triN;
      vecSub(&(verts[p3].position), &(verts[p2].position), &v1);
      vecSub(&(verts[p1].position), &(verts[p2].position), &v2);
      vecCross(&v1, &v2, &triN);
      normalize(&triN);

      /* add this normal to each adjacent vertex normal */
      vecAdd(&triN, &verts[p1].normal, &verts[p1].normal);
      vecAdd(&triN, &verts[p2].normal, &verts[p2].normal);
      vecAdd(&triN, &verts[p3].normal, &verts[p3].normal);

      facesPerVert[p1]++;
      facesPerVert[p2]++;
      facesPerVert[p3]++;

      pNdx += 3;
   }

   /* each vertex normal now contains the sum of adjacent face normals;
      take the average for each and then normalize */
   for (i = 0; i < numVerts; i++)
   {
      vecScale(&verts[i].normal, 1.0 / facesPerVert[i]);
      normalize(&verts[i].normal);
   }
}

