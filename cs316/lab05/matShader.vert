#version 120
// file: matShader.vert
// Evan Conley, 11/2/2017

// gl_Vertex contains the incoming vertex coordinates
uniform mat4 R;
uniform mat4 S;
uniform mat4 T;
uniform mat4 projection;

void main(void) {
    mat4 modelView = T * S * R;
    float x = gl_Vertex.x;
    float y = gl_Vertex.y;
   
    vec4 transVert = modelView * vec4(x,y,0.0,1.0); 
    gl_Position = projection * transVert;
}
