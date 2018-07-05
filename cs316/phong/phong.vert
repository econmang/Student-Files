#version 120
// file: phong.vert
// CS316 Phong Shading and Lighting Example
// Kevin Sahr, 11/9/17

// the MVP matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

// per-vertex inputs
attribute vec4 position; // replaces gl_Vertex
attribute vec4 normal;

// pass the vectors to the fragment shader
varying vec3 N;
varying vec3 L;
varying vec3 V;

// light position
// we will use hard-coded values for this example
uniform vec4 lightPosition = vec4(2.0, 2.0, 5.0, 1.0);

void main(void) {

    // create the modelview matrix
    mat4 modelview = view * model;

    // calculate the position in view space
    vec4 P = modelview * position;

    // calculate normal in view space
    N = normalize(vec3(modelview * normal));

    // calculate view-space light vector
    // first transform the lightPosition by the view matrix (but not
    // the model matrix)
    vec3 LP = vec3(view * lightPosition);
    L = normalize(LP - P.xyz);

    // calculate view vector (simply the negative of the view-space 
    // position since the eye is at the origin in view-space)
    V = normalize(-P.xyz);

    // apply the projection to the view space position to
    // get the final vertex position
    gl_Position = proj * P;
}
