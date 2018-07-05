/*
   glfuncs.c: function definitions for cs316 lab 3
   Created by: Kevin Sahr, 10/5/17
*/

#include <math.h>
#include <string.h>
#include "glfuncs.h" 

void drawVerts(GLuint drawType, const Vec2D verts[], int numVerts) {
   if (drawType == GL_POINTS)
      drawPoints(verts, numVerts);
   else if (drawType == GL_LINE_STRIP)
      drawPolyline(verts, numVerts);
   else if (drawType == GL_LINE_LOOP)
      drawPolygon(verts, numVerts);
   else
      fprintf(stderr, "ERROR: unknown drawing type.\n");
}

void drawPoints (const Vec2D pts[], int numPts) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, pts);
    glDrawArrays(GL_POINTS, 0, numPts);
}

void drawPolyline (const Vec2D pts[], int numPts) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, pts);
    glDrawArrays(GL_LINE_STRIP, 0, numPts);
}

void drawPolygon (const Vec2D pts[], int numPts) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, pts);
    glDrawArrays(GL_LINE_LOOP, 0, numPts);
}

int readOneVert (FILE* inFile, Vec2D* v) {
   char str[MAXLINE];
   if (!fgets(str, MAXLINE, inFile))
      return 1;
   else if (sscanf(str, "%f %f", &v->x, &v->y) != 2)
      return 1;
   else // success
      return 0;
}

int readVertFile (const char* fileName, Vec2D* verts) {

   // open the file for reading
   FILE* inFile = fopen(fileName, "r");
   if (!inFile)
   {
      fprintf(stderr, "ERROR: file %s not found.\n", fileName);
      return 0;
   }

   // read i,j,k triplets from file until EOF
   int numVerts = 0;
   while (1) { // infinite loop

      if (numVerts >= MAXVERTS) {
         fprintf(stderr, "ERROR: input file exceeds max number of vertices %d\n", MAXVERTS);
         numVerts = 0; // 0 indicates an error
         break;
      }

      // read a single line
      if (readOneVert(inFile, &verts[numVerts])) {
         if (feof(inFile)) // at EOF
            break;
         else { // must be an error
            fprintf(stderr, "ERROR: reading file %s\n", fileName);
            numVerts = 0; // 0 indicates an error
            break;
         }
      } 

      numVerts++;
   }

   fclose(inFile);

   return numVerts;
}

int readOneSpec (FILE* inFile, DrawSpec* d) {
   char str[MAXLINE];
   char typeStr[MAXLINE];
   if (!fgets(str, MAXLINE, inFile))
      return 1;
   else if (sscanf(str, "%s %f %f %f %f %f %f %f %f %f", 
            typeStr, &d->rotRads, &d->scale[0], &d->scale[1], 
            &d->trans[0], &d->trans[1], &d->rgba[0], &d->rgba[1], 
            &d->rgba[2], &d->rgba[3]) != 10)
      return 1;
   else // success
   {
      // parse the graphics primitive type
      if (!strcmp(typeStr, "POINTS"))
         d->drawType = GL_POINTS;
      else if (!strcmp(typeStr, "LINES"))
         d->drawType = GL_LINE_STRIP;
      else if (!strcmp(typeStr, "POLY"))
         d->drawType = GL_LINE_LOOP;
      else {
         fprintf(stderr,
            "ERROR: invalid graphics primitive \"%s\"\n", typeStr);
         return 1;
      }
      
      // convert the rotation angle to radians
      d->rotRads *= M_PI / 180.0; 

      // we might also validate the RGBA values here
   
      return 0;
   }
}

int readSpecFile (const char* fileName, DrawSpec* specs) {

   // open the file for reading
   FILE* inFile = fopen(fileName, "r");
   if (!inFile)
   {
      fprintf(stderr, "ERROR: file %s not found.\n", fileName);
      return 0;
   }

   // read drawing specifications until EOF
   int numSpecs = 0;
   while (1) { // infinite loop

      if (numSpecs >= MAXSPEC) {
         fprintf(stderr, "ERROR: input file exceeds max number of specifications %d\n", MAXSPEC);
         numSpecs = 0; // 0 indicates an error
         break;
      }

      // read a single line
      if (readOneSpec(inFile, &specs[numSpecs])) {
         if (feof(inFile)) // at EOF
            break;
         else { // must be an error
            fprintf(stderr, "ERROR: reading file %s\n", fileName);
            numSpecs = 0; // 0 indicates an error
            break;
         }
      } 

      numSpecs++;
   }

   fclose(inFile);

   return numSpecs;
}

