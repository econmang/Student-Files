#version 120
// file: labThree.vert
// vertex shader that rotates, scales, and then translates vertices
// Created by: Evan Conley, 10/24/2017

   uniform float theta;
   uniform float xscale;
   uniform float yscale;
   uniform float xtrans;
   uniform float ytrans;

void main(void){

   //rotate vertices
   float x2 = gl_Vertex.x * cos(theta) - gl_Vertex.y * sin(theta);
   float y2 = gl_Vertex.y * cos(theta) + gl_Vertex.x * sin(theta);

   //scale vertices
   x2 = x2 * xscale;
   y2 = y2 * yscale;


   //translate vertices
   x2 = x2 + xtrans;
   y2 = y2 + ytrans;

   //set new coords
   gl_Position = vec4(x2, y2, 0.0, 1.0);
}
