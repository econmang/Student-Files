#version 120
// file: default.vert
// default vertex shader that passes 2D position through unchanged
// Kevin Sahr, 10/11/17

void main(void) {
    // gl_Vertex contains the incoming vertex coordinates
    // gl_Position should contain the transformed coordinates
    gl_Position = vec4(gl_Vertex.x, gl_Vertex.y, 0.0, 1.0);
}
