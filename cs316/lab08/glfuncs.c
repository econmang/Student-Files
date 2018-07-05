/*
   glfuncs.c: function definitions for cs316 lab 6
   Created by: Kevin Sahr, 11/19/17
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "glfuncs.h" 

void loadObject (const char* fileName, Vec3D* verts, GLuint* faces, 
                 GLuint* numVerts, GLuint* numFaces, RGBA* col)
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

   /* get the color */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &col->r, &col->g, &col->b, &col->a) != 4)
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
      if (sscanf(nextLine, "%d %f %f %f", &n, &(verts[i].x), &(verts[i].y),
               &(verts[i].z)) != 4) {
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

void loadLight(const char* fileName, Vec3D lightpos, RGBA amb, RGBA diff, RGBA spec) {
   FILE* fp;
   char nextLine[MAX_LINE];

   /* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: file %s not found\n", fileName);
      exit(1);
   }

   getNextLine(nextLine, fp, 0);
   printf("Here..\n\n");
   if (sscanf(nextLine, "%f %f %f", &lightpos.x, &lightpos.y, &lightpos.z) != 3)
   {
      fprintf(stderr, "ERROR: invalid file format in light position\n");
      exit(2);
   }
   printf("\nLoaded successfully\n\n");

   /* get the number of vertices */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &amb.r, &amb.g, &amb.b, &amb.a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in light position\n");
      exit(2);
   }

   /* get the number of vertices */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &diff.r, &diff.g, &diff.b, &diff.a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in light position\n");
      exit(2);
   }

   /* get the number of vertices */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &spec.r, &spec.g, &spec.b, &spec.a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in light position\n");
      exit(2);
   }
   fclose(fp);
}

void loadMaterial(const char* fileName, RGBA em, GLfloat *ka, GLfloat *kd, GLfloat *ks, GLfloat *ns) {
   FILE* fp;
   char nextLine[MAX_LINE];

	/* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: file %s not found\n", fileName);
      exit(1);
   }

   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &em.r, &em.g, &em.b, &em.a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in em RGBA\n");
      exit(2);
   }

   /* get the number of vertices */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f", ka, kd, ks) != 3)
   {
      fprintf(stderr, "ERROR: invalid file format in material constants\n");
      exit(2);
   }

    getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f", ns) != 1)
   {
      fprintf(stderr, "ERROR: invalid file format in material constants\n");
      exit(2);
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


Vec3D normalize(Vec3D vector) {
    GLfloat x = vector.x;
    GLfloat y = vector.y;
    GLfloat z = vector.z;
    GLfloat magnitude = sqrt((x*x) + (y*y) + (z*z));
    vector.x = x/magnitude;
    vector.y = y/magnitude;
    vector.z = z/magnitude;
    return vector;
}

Vec3D crossProduct(Vec3D A, Vec3D B) {
    /*
     * cx = aybz - azby
     * cy = azbx - axbz
     * cz = axby - aybx
     *
     * */

    Vec3D C;
    C.x = A.y*B.z - A.z*B.y;
    C.y = A.z*B.x - A.x*B.z;
    C.z = A.x*B.y - A.y*B.x;
    return C;
}

Vec3D vecAddition(Vec3D A, Vec3D B) {
    Vec3D addVec;
    addVec.x = A.x + B.x;
    addVec.y = A.y + B.y;
    addVec.z = A.z + B.z;
    return addVec;
}

Vec3D vecSubtract(Vec3D A, Vec3D B) {
    Vec3D subVec;
    subVec.x = A.x - B.y;
    subVec.y = A.y - B.y;
    subVec.z = A.z - B.z;
    return subVec;
}


















