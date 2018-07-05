#version 120
// file: default.frag
// default fragment shader: sets all fragments to white.
// Kevin Sahr, 10/11/17

void main(void) {
    // gl_FragColor is a built-in variable that holds the
    // final color for this fragment
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
