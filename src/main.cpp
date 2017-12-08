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
#include <vector>

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
#include "Renderer.h"
#include "Loader.h"

// Screen Resolution
#define WIDTH   800
#define HEIGHT  600





int main()
{
    Graphics::Window::create("Bomberman - Farm Edition", WIDTH, HEIGHT);
    Input::Keyboard::init();
    Input::Mouse::init();

    Graphics::Loader loader;
    Graphics::Renderer renderer;

    std::vector<GLfloat> vertices = {

        -0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f
    };

    std::vector<GLuint> indices = {
        0, 1, 3,
        3, 1, 2
    };

    Graphics::RawModel model = loader.loadToVAO(vertices, indices);

    // System's GPU information
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer_gl    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer_gl, glversion, glslversion);

    // Setting up shaders
    Shaders::setup();

    while (!Graphics::Window::shouldClose())
    {
        renderer.prepare();
        Shaders::start();
        renderer.render(model);
        Shaders::stop();
        Graphics::Window::updateScreen();
    }

    Shaders::cleanUp();
    loader.cleanUp();
    Graphics::Window::destroy();
}

