#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "AttributeLocation.h"

namespace Shaders
{
    // PATH to GLSL shaders
    #define PATH_VERTEX_SHADER "../../src/Shaders/shader_vertex.glsl"
    #define PATH_FRAGMENT_SHADER "../../src/Shaders/shader_fragment.glsl"

    static GLuint program_id;
    static GLuint vertex_shader_id;
    static GLuint fragment_shader_id;

    // Load a shader from a GLSL file
    void LoadShader(const char* filename, GLuint shader_id);

    // Shader loader for each kind of shader
    void LoadShader_Vertex(const char* filename);
    void LoadShader_Fragment(const char* filename);

    // Uses the shaders to create a program that runs on the GPU
    void CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);

    void setup();
    void start();
    void stop();
    void cleanUp();
    void bindAttributes();
    void bindAttribute(AttributeLocation attribute, const char* variableName);
}

#endif // SHADERS_H
