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

// Screen Resolution
#define WIDTH   800
#define HEIGHT  600

int main()
{
    Window::create("Bomberman - Farm Edition", WIDTH, HEIGHT);
    Keyboard::init();
    Mouse::init();

    std::cout << glGetString(GL_VERSION) << std::endl;

    while (!Window::shouldClose())
    {
        double x, y;
        Mouse::getCursorPosition(x, y);
        std::cout << x << std::endl;
        Window::clearBuffer();
        Window::updateScreen();
    }

    Window::destroy();
}

