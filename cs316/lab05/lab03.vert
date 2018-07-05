#version 120
// file: lab03.vert
// Kevin Sahr, 10/11/17

// gl_Vertex contains the incoming vertex coordinates
uniform float theta;
uniform vec2 scale;
uniform vec2 trans;

void main(void) {

    // rotate
    // for efficiency, do the sin and cos once 
    float cosTheta = cos(theta); 
    float sinTheta = sin(theta); 

    float x = gl_Vertex.x * cosTheta - gl_Vertex.y * sinTheta;
    float y = gl_Vertex.y * cosTheta + gl_Vertex.x * sinTheta;

    // scale
    x *= scale.x;
    y *= scale.y;

    // translate
    x += trans.x;
    y += trans.y;

    // gl_Position is the transformed vertex
    gl_Position = vec4(x, y, 0.0, 1.0);
}
