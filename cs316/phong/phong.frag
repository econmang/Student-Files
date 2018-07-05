#version 120
// file: phong.frag
// Kevin Sahr, 11/19/17

// the vectors are interpolated from the vertex
// shader outputs
varying vec3 N;
varying vec3 L;
varying vec3 V;

// light properties
// we will use hard-coded values for this example
uniform vec3 lightDiffuse = vec3(0.5, 0.2, 0.7);
uniform vec3 lightSpecular = vec3(0.7, 0.7, 0.7);
uniform vec3 lightAmbient = vec3(0.2, 0.2, 0.2);

// material properties
uniform vec3 emissive = vec3(0.2,0.5,0.5);
uniform float ka = 0.9;
uniform float kd = 1.0;
uniform float ns = 110.0; // 1.0 - 128.0
uniform float ks = 1.0;

void main(void) {
    // normalize the incoming N, L and V vectors
    vec3 Nn = normalize(N);
    vec3 Ln = normalize(L);
    vec3 Vn = normalize(V);

    // calculate R locally
    vec3 R = reflect(-Ln, Nn);

    // calculate the ambient, diffuse and specular contributions
    vec3 ambient = ka * lightAmbient;
    vec3 diffuse = kd * max(dot(Nn, Ln), 0.0) * lightDiffuse;
    vec3 specular = ks * pow(max(dot(R, Vn), 0.0), ns) * lightSpecular;

    // write final color to the framebuffer
    gl_FragColor = vec4(emissive + ambient + diffuse + specular, 1.0);
}
