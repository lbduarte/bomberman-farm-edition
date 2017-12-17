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
#define SECONDS 60
#define BOMBS 20
#define BOMB_TIME 5

GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id); // Cria um programa de GPU

void TextRendering_Init();
float TextRendering_LineHeight(GLFWwindow* window);
float TextRendering_CharWidth(GLFWwindow* window);
void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);

int main()
{
    Graphics::Window::create("Bomberman - Farm Edition", WIDTH, HEIGHT);
    Input::Keyboard::init();
    Input::Mouse::init();

    Graphics::Loader loader;
    Graphics::Renderer renderer;
    Cameras::LookAt::init(0.0f, 3*(M_PI/4), 13.0f, glm::vec4(0.0f, -2.0f, -2.0f, 1.0f),glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

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
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "BombDifuse"), 4);
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "BombNormal"), 5);
    glUniform1i(glGetUniformLocation(Shaders::getProgramID(), "BombSpecular"), 6);
    glUseProgram(0);

    loader.loadTextureImage("../../data/grass.jpeg"); //Grass
    loader.loadTextureImage("../../data/fence.jpeg"); //Fence
    loader.loadTextureImage("../../data/hay_cube.jpg"); //HayCube
    loader.loadTextureImage("../../data/wood_cube.jpg"); //WoodCube
    loader.loadTextureImage("../../data/bomb_difuse_map.jpg"); //WoodCube
    loader.loadTextureImage("../../data/bomb_normal_map.jpg"); //BombNormal
    loader.loadTextureImage("../../data/bomb_specular_map.jpg"); //BombSpecular

    glm::mat4 modelMatrix;

    // Inicializamos o código para renderização de texto.
    TextRendering_Init();

    glEnable(GL_DEPTH_TEST);

    int seconds = SECONDS;
    int time = (int)glfwGetTime();

    int bombs = BOMBS;
    bool start = false;
    bool activeBomb = false;

    glm::vec4 bombPosition;

    int bombCountdown;

    while (!Graphics::Window::shouldClose())
    {
        renderer.prepare();
        Shaders::start();
        if(!start)
        {
            Cameras::LookAt::computePosition();

            Cameras::LookAt::computeViewMatrix();
            Projection::init();
            Projection::computeProjectionMatrix();
            glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(Cameras::LookAt::getViewMatrix()));
            glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(Projection::getProjectionMatrix()));
            Graphics::VirtualScene::drawObjects(model_uniform, object_id_uniform, renderer, false);

            char buffer[25] = "press ENTER to start";
            int numchars=25;
            float lineheight = TextRendering_LineHeight(Graphics::Window::getWindow());
            float charwidth = TextRendering_CharWidth(Graphics::Window::getWindow());
            TextRendering_PrintString(Graphics::Window::getWindow(), buffer, 1.0f-(numchars + 1)*charwidth, 1.0f-lineheight, 1.0f);

            if (Input::Keyboard::isKeyPressed(GLFW_KEY_ENTER))
            {
                start = true;
                Cameras::Free::init(0.0f, 0.0f, -2.5f, glm::vec4(5.0f, -1.5f, 3.0f, 1.0f), glm::vec4(0.0f, 0.0f, -2.5f, 0.0f));
                //Cameras::Free::init(0.0f, 0.0f, -2.5f, glm::vec4(0.0f, 0.0f, 2.5f, 1.0f), glm::vec4(0.0f, 0.0f, -2.5f, 0.0f));
            }
        }
        else
        {
            Cameras::Free::updateCamera();
            Cameras::Free::computeViewMatrix();
            Projection::init();
            Projection::computeProjectionMatrix();
            glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(Cameras::Free::getViewMatrix()));
            glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(Projection::getProjectionMatrix()));
            Graphics::VirtualScene::drawObjects(model_uniform, object_id_uniform, renderer, true);

            if (Input::Keyboard::isKeyPressed(GLFW_KEY_SPACE)  && !activeBomb){
                activeBomb = true;
                bombPosition = Cameras::Free::getPosition();
                bombCountdown = BOMB_TIME;
            }
            if(activeBomb && bombCountdown > 0){
                Graphics::VirtualScene::drawBomb(model_uniform, object_id_uniform, renderer, bombPosition);
            }
            if(bombCountdown == 0){
                activeBomb = false;
                //demolir blocos
            }

            if(time != (int)glfwGetTime())
            {
                time =(int)glfwGetTime();
                seconds--;
                if(activeBomb){
                    bombCountdown--;
                }
            }

            //Print # of bombs and # of remaining secs
            char buffer[25];
            int numchars=25;
            sprintf ( buffer, "%d bombs      %dsecs", bombs, seconds );
            float lineheight = TextRendering_LineHeight(Graphics::Window::getWindow());
            float charwidth = TextRendering_CharWidth(Graphics::Window::getWindow());
            TextRendering_PrintString(Graphics::Window::getWindow(), buffer, 1.0f-(numchars + 1)*charwidth, 1.0f-lineheight, 1.0f);

        }
        Shaders::stop();
        Graphics::Window::updateScreen();
    }

    Shaders::cleanUp();
    loader.cleanUp();
    Graphics::Window::destroy();
}

GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    // Criamos um identificador (ID) para este programa de GPU
    GLuint program_id = glCreateProgram();

    // Definição dos dois shaders GLSL que devem ser executados pelo programa
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    // Linkagem dos shaders acima ao programa
    glLinkProgram(program_id);

    // Verificamos se ocorreu algum erro durante a linkagem
    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    // Imprime no terminal qualquer erro de linkagem
    if ( linked_ok == GL_FALSE )
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        // Alocamos memória para guardar o log de compilação.
        // A chamada "new" em C++ é equivalente ao "malloc()" do C.
        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::string output;

        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "\n== End of link log\n";

        // A chamada "delete" em C++ é equivalente ao "free()" do C
        delete [] log;

        fprintf(stderr, "%s", output.c_str());
    }

    // Os "Shader Objects" podem ser marcados para deleção após serem linkados
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    // Retornamos o ID gerado acima
    return program_id;
}
