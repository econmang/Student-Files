/*
   draw.c: cs316 phong shading with Phong lighting example
   Created by: Kevin Sahr
*/

#include <stdio.h>
#include <stdlib.h>
#include "glfuncs.h"
#include "shader.h"

// the shader program
// declared in the main file
extern GLuint shaderProgram;

// each Vertex has a position and normal
// since this is an origin-centered regular polyhedron the normals
// are the same as the vertex coordinates
#define X .525731112119133606
#define Z .850650808352039932
static Vertex verts[] = {
   {{ -X, 0.0,   Z}, { -X, 0.0,   Z}}, // vert 0 xyz and normal
   {{  X, 0.0,   Z}, {  X, 0.0,   Z}}, 
   {{ -X, 0.0,  -Z}, { -X, 0.0,  -Z}}, 
   {{  X, 0.0,  -Z}, {  X, 0.0,  -Z}},
   {{0.0,   Z,   X}, {0.0,   Z,   X}}, 
   {{0.0,   Z,  -X}, {0.0,   Z,  -X}}, 
   {{0.0,  -Z,   X}, {0.0,  -Z,   X}}, 
   {{0.0,  -Z,  -X}, {0.0,  -Z,  -X}},
   {{  Z,   X, 0.0}, {  Z,   X, 0.0}}, 
   {{ -Z,   X, 0.0}, { -Z,   X, 0.0}}, 
   {{  Z,  -X, 0.0}, {  Z,  -X, 0.0}}, 
   {{ -Z,  -X, 0.0}, { -Z,  -X, 0.0}}
};

static GLuint faces [20][3] = {
   {1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4}, 
   {1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2}, 
   {3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0}, 
   {10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7} 
};

const int numVerts = 60;

void drawIcosahedron (void)
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
   glDrawElements(GL_TRIANGLES, numVerts, GL_UNSIGNED_INT, NULL);
}
