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
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Shaders.h"
#include "Renderer.h"
#include "Loader.h"
#include "LookAtCamera.h"
#include "FreeCamera.h"
#include "Projection.h"

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
    Cameras::LookAt::init(0.0f, 0.0f, -2.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    Cameras::Free::init(0.0f, 0.0f, -2.5f, glm::vec4(0.0f, 0.0f, 2.5f, 1.0f), glm::vec4(0.0f, 0.0f, -2.5f, 0.0f));

    std::vector<GLfloat> model_coefficients = {
    // Vértices de um cubo
    //    X      Y     Z     W
        -0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 0
        -0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 1
         0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 2
         0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 3
        -0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 4
        -0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 5
         0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 6
         0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 7
    };

    std::vector<GLuint> indices = {
        0, 1, 2, // triângulo 1
        7, 6, 5, // triângulo 2
        3, 2, 6, // triângulo 3
        4, 0, 3, // triângulo 4
        4, 5, 1, // triângulo 5
        1, 5, 6, // triângulo 6
        0, 2, 3, // triângulo 7
        7, 5, 4, // triângulo 8
        3, 6, 7, // triângulo 9
        4, 3, 7, // triângulo 10
        4, 1, 0, // triângulo 11
        1, 6, 2, // triângulo 12
    };

    std::vector<GLfloat> color_coefficients = {
    // Cores dos vértices do cubo
    //  R     G     B     A
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 0
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 1
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 2
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 3
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 4
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 5
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 6
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 7
    };

    Graphics::ObjModel obj("../../data/bunny.obj");
    obj.computeNormals();
    obj.buildTriangles();
    Graphics::RawModel model = loader.loadObjToVAO(obj);
//    Graphics::RawModel model = loader.loadToVAO(model_coefficients, indices, color_coefficients);

    // System's GPU information
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer_gl    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer_gl, glversion, glslversion);

    // Setting up shaders
    Shaders::setup();

    GLint model_uniform           = glGetUniformLocation(Shaders::getProgramID(), "model");
    GLint view_uniform            = glGetUniformLocation(Shaders::getProgramID(), "view");
    GLint projection_uniform      = glGetUniformLocation(Shaders::getProgramID(), "projection");
    glm::mat4 modelMatrix;

    glEnable(GL_DEPTH_TEST);

    while (!Graphics::Window::shouldClose())
    {

        renderer.prepare();
        Shaders::start();
        Cameras::Free::computePosition();
        Cameras::Free::computeViewMatrix();
        Projection::init();
        Projection::computeProjectionMatrix();
        glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(Cameras::Free::getViewMatrix()));
        glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(Projection::getProjectionMatrix()));
        modelMatrix = Matrix_Identity();
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        renderer.render(model);
        Shaders::stop();
        Graphics::Window::updateScreen();
    }

    Shaders::cleanUp();
    loader.cleanUp();
    Graphics::Window::destroy();
}

