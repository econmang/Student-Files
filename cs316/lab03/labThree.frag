#version 120
// file: labThree.frag
// fragment shader that sets fragments to specified color
// Created by: Evan Conley
// 10/24/2017

   uniform vec4 fragColor;

void main(void){
   gl_FragColor = fragColor;
}