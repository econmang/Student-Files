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

void loadLight (const char* fileName, RGBA* lAmb, RGBA* lDiff, 
                 RGBA* lSpec, Vec3D* lPos)
{
   FILE* fp;
   char nextLine[MAX_LINE];

   /* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: file %s not found\n", fileName);
      exit(1);
   }

   /* get the lightPos */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f", &lPos->x, &lPos->y, &lPos->z) != 3 )
   {
      fprintf(stderr, "ERROR: invalid file format in light position\n");
      exit(2);
   }

   /* get the ambient light */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &lAmb->r, &lAmb->g, &lAmb->b, &lAmb->a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in ambient light\n");
      exit(2);
   }
   else if(colorCheck(*lAmb))
   {
      fprintf(stderr, "ERROR: invalid file format in ambient light\n");
      exit(2);
   }
   

   /* get the diffused light */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &lDiff->r, &lDiff->g, &lDiff->b, &lDiff->a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in diffused light\n");
      exit(2);
   }
   else if(colorCheck(*lDiff))
   {
      fprintf(stderr, "ERROR: invalid file format in diffused light\n");
      exit(2);
   }

   /* get the specular light */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &lSpec->r, &lSpec->g, &lSpec->b, &lSpec->a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in specular light\n");
      exit(2);
   }
   else if(colorCheck(*lSpec))
   {
      fprintf(stderr, "ERROR: invalid file format in specular light\n");
      exit(2);
   }
}

void loadMat (const char* fileName, RGBA* emis, K* k, GLuint* n)
{
   FILE* fp;
   char nextLine[MAX_LINE];

   /* open the file */
   if ((fp = fopen(fileName, "r")) == NULL)
   {
      fprintf(stderr, "ERROR: file %s not found\n", fileName);
      exit(1);
   }

   /* get the emissive property */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f %f", &emis->r, &emis->g, &emis->b, &emis->a) != 4)
   {
      fprintf(stderr, "ERROR: invalid file format in emissive prop\n");
      exit(2);
   }
   else if(colorCheck(*emis))
   {
      fprintf(stderr, "ERROR: invalid file format in emissive prop\n");
      exit(2);
   }

   /* get the k values */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%f %f %f", &k->a, &k->d, &k->s) != 3 )
   {
      fprintf(stderr, "ERROR: invalid file format in k values\n");
      exit(2);
   }

   /* get the n value */
   getNextLine(nextLine, fp, 0);
   if (sscanf(nextLine, "%d", n) != 1)
   {
      fprintf(stderr, "ERROR: invalid file format in n value\n");
      exit(2);
   }
   else if(*n > 128 || *n < 0)
   {
      fprintf(stderr, "ERROR: invalid file format in n value\n");
      exit(2);
   }
   
}

int colorCheck(RGBA col)
{
   if(col.r > 1.0 || col.g > 1.0 || col.b > 1.0 || col.a > 1.0)
      return 1;
   else if(col.r < 0.0 || col.g < 0.0 || col.b < 0.0 || col.a < 0.0)
      return 1;
   else
      return 0;
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

