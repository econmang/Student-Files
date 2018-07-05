#version 120
// file: proj.vert
// CS316 3D wireframe example
// Kevin Sahr, 11/9/17

// mat4 is the 4x4 matrix type
uniform mat4 view;
uniform mat4 proj;

void main(void) {

    // apply V and P matrices to the vertex
    gl_Position = proj * view * gl_Vertex;
}
