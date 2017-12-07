//     Universidade Federal do Rio Grande do Sul
//             Instituto de Informática
//       Departamento de Informática Aplicada
//
// INF01047 Fundamentos de Computação Gráfica 2017/2
//               Prof. Eduardo Gastal
//
//                   TRABALHO FINAL
//
//              BOMBERMAN - FARM EDITION
//
//  Aline Weber
//  Leonardo Duarte
//  Renan Kummer


// C Header Files
#include <cmath>
#include <cstdio>
#include <cstdlib>

// C++ Header files
#include <map>
#include <string>
#include <fstream>
#include <sstream>

// OpenGL Libraries
#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library

// GLM Headers for using matrices and vectors
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Local Headers located in folder "include/"
#include "matrices.h"

// Windowing
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Shaders.h"

// Screen Resolution
#define WIDTH   800
#define HEIGHT  600

// PATH to GLSL shaders
#define PATH_VERTEX_SHADER "../../src/Shaders/shader_vertex.glsl"
#define PATH_FRAGMENT_SHADER "../../src/Shaders/shader_fragment.glsl"

int main()
{
    Graphics::Window::create("Bomberman - Farm Edition", WIDTH, HEIGHT);
    Input::Keyboard::init();
    Input::Mouse::init();

    // System's GPU information
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    // Setting up shaders
    GLuint vertex_shader_id = Shaders::LoadShader_Vertex(PATH_VERTEX_SHADER);
    GLuint fragment_shader_id = Shaders::LoadShader_Fragment(PATH_FRAGMENT_SHADER);
    GLuint program_id = Shaders::CreateGpuProgram(vertex_shader_id, fragment_shader_id);

    while (!Graphics::Window::shouldClose())
    {
        Graphics::Window::clearBuffer();
        Graphics::Window::updateScreen();
    }

    Graphics::Window::destroy();
}

