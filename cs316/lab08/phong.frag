#version 120
// file: phong.frag
// Kevin Sahr, 11/19/17

// the vectors are interpolated from the vertex
// shader outputs
varying vec3 N;
varying vec3 L;
varying vec3 V;

// light properties
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform vec3 lightAmbient;

// material properties
uniform vec3 emissive;
uniform float ka;
uniform float kd;
uniform float ns;
uniform float ks;

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
