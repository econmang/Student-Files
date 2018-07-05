/*
   glfuncs.c: function definitions for cs316 lab 2
   Created by: Kevin Sahr, 10/5/17
*/

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

   // read x,y from file until EOF
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

