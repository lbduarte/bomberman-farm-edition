#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

namespace Shaders
{
    // Load a shader from a GLSL file
    void LoadShader(const char* filename, GLuint shader_id);

    // Shader loader for each kind of shader
    GLuint LoadShader_Vertex(const char* filename);
    GLuint LoadShader_Fragment(const char* filename);

    // Uses the shaders to create a program that runs on the GPU
    GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
}

#endif // SHADERS_H
