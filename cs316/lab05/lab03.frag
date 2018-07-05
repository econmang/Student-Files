#version 120
// file: lab03.frag
// Kevin Sahr, 10/26/17

uniform vec4 fragColor;

void main(void) {
    // gl_FragColor is a built-in variable that holds the
    // final color for this fragment
    gl_FragColor = fragColor;
}
