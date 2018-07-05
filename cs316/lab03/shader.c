/*
   shader.c: shader-related functions
   Created by: Kevin Sahr, 10/11/17
*/

#include <stdlib.h>
#include "shader.h"

// creates and returns a shader program given the names of text files
// containing the vertex and shader programs
GLuint createShaderProgram (const char* vertFileName, const char* fragFileName) {

    // the shader source code strings
    GLchar *vertSource, *fragSource;
    // handles for the two shaders
    GLuint vertShader, fragShader;
    // handle for the shader program
    GLuint shaderProgram;

    // read the shaders into the appropriate string buffers
    vertSource = fileToString(vertFileName);
    if (!vertSource) {
       fprintf(stderr, "ERROR: file '%s' does not exist.\n", vertFileName);
       exit(4);
    }

    fragSource = fileToString(fragFileName);
    if (!fragSource) {
       fprintf(stderr, "ERROR: file '%s' does not exist.\n", fragFileName);
       exit(4);
    }

    // create an empty vertex shader handle
    vertShader = glCreateShader(GL_VERTEX_SHADER);

    // create the vertex shader from the source string
    glShaderSource(vertShader, 1, (const GLchar**)&vertSource, 0);
    free(vertSource);

    // compile the vertex shader and check for success 
    glCompileShader(vertShader);

    int success;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
       fprintf(stderr, "ERROR: vertex shader compilation failed.\n");
       exit(5);
    }

    // create an empty fragment shader handle 
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // create the fragment shader from the source string
    glShaderSource(fragShader, 1, (const GLchar**)&fragSource, 0);

    // compile the fragment shader and check for success 
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
       fprintf(stderr, "ERROR: fragement shader compilation failed.\n");
       exit(5);
    }

    // if we're here the vertex and fragment shaders have successfully
    // compiled. Now link them together into a single GL shader program
    // and load onto the GPU.

    // get the shader program handle
    shaderProgram = glCreateProgram();

    // attach the shaders to the program
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    // link the program
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&success);
    if (!success) {
       fprintf(stderr, "ERROR: shader linking failed.\n");
       exit(5);
    }

    // load the shader into the rendering pipeline
    glUseProgram(shaderProgram);

    return shaderProgram;
}

// Allocate a char buffer and read a file into it.
// Returns the char buffer or 0 on error. 
char* fileToString(const char *fileName)
{
    FILE *fptr;
    long length;
    char *buf;

    // open file for reading
    fptr = fopen(fileName, "rb");
    if (!fptr) return 0;

    // allocate the buffer based on the file length
    fseek(fptr, 0, SEEK_END); /* Seek to end of file */
    length = ftell(fptr); /* find how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* remember space for null terminator */

    // read the file into the buffer
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); 
    buf[length] = '\0';

    // clean-up
    fclose(fptr);

    return buf;
}

