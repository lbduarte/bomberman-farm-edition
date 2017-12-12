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
#include "ObjectId.h"
#include "VirtualScene.h"

// Screen Resolution
#define WIDTH   800
#define HEIGHT  600

#define M_PI 3.1415

int main()
{
    Graphics::Window::create("Bomberman - Farm Edition", WIDTH, HEIGHT);
    Input::Keyboard::init();
    Input::Mouse::init();

    Graphics::Loader loader;
    Graphics::Renderer renderer;
    Cameras::LookAt::init(0.0f, 0.0f, -2.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    Cameras::Free::init(0.0f, 0.0f, -2.5f, glm::vec4(5.0f, -1.5f, 3.0f, 1.0f), glm::vec4(0.0f, 0.0f, -2.5f, 0.0f));

    Graphics::VirtualScene::init(loader);

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
    GLint object_id_uniform       = glGetUniformLocation(Shaders::getProgramID(), "object_id");

    // Variáveis em "shader_fragment.glsl" para acesso das imagens de textura
    glUseProgram(Shaders::getProgramID());
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "Grass"), 0);
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "Fence"), 1);
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "HayCube"), 2);
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "WoodCube"), 3);
    glUseProgram(0);

    loader.loadTextureImage("../../data/grass.jpeg"); //Grass
    loader.loadTextureImage("../../data/fence.jpeg"); //Fence
    loader.loadTextureImage("../../data/hay_cube.jpg"); //HayCube
    loader.loadTextureImage("../../data/wood_cube.jpg"); //WoodCube

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

        Graphics::VirtualScene::drawObjects(model_uniform, object_id_uniform, renderer);

        Shaders::stop();
        Graphics::Window::updateScreen();
    }

    Shaders::cleanUp();
    loader.cleanUp();
    Graphics::Window::destroy();
}

