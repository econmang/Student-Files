#version 120
// file: proj.vert
// CS316 Lab 6
// Kevin Sahr, 11/9/17

// mat4 is the 4x4 matrix type
uniform mat4 view;
uniform mat4 scale;
uniform mat4 rotate;
uniform mat4 proj;

void main(void) {

    mat4 model = rotate * scale;

    // apply MVP matrices to the vertex
    gl_Position = proj * view * model * gl_Vertex;
}
