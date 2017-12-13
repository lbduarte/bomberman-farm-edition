#include "Window.h"

using namespace Graphics;
using namespace Window;

void Window::create(const char* p_title, int p_width, int p_height)
{
    title = p_title;
    width = p_width;
    height = p_height;
    screenRatio = (float) width/height;

    if (!init())
    {
        std::cout << "Could not initialize window!" << std::endl;
        glfwTerminate();
    }

}

void Window::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::frameBufferSizeCallback(GLFWwindow* p_window, int p_width, int p_height)
{
    width = p_width;
    height = p_height;
    screenRatio = (float) width/height;
    glViewport(0, 0, width, height);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

float Window::getScreenRatio()
{
    return screenRatio;
}

bool Window::init()
{

    // Initializing GLFW library
    if (!glfwInit())
    {
        std::cout << "Error Initializing GLFW" << std::endl;
        return false;
    }

    // OpenGl context creation settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    // Error checking
    if (!window)
    {
        glfwTerminate();
        std::cout << "GLFW Window Creation Failed!" << std::endl;
        return false;
    }

    // Setting window as the current context
    glfwMakeContextCurrent(window);

    // Interval between screen updates to prevent screen tearing
    glfwSwapInterval(1);

    // Getting OpenGL functions using glad library
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // Setting callbacks
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, Input::Keyboard::keyCallback);

    glfwSetCursorPosCallback(window, Input::Mouse::cursorPosCallback);
    glfwSetMouseButtonCallback(window, Input::Mouse::mouseButtonCallback);
    glfwSetScrollCallback(window, Input::Mouse::scrollCallback);


    return true;
}

void Window::updateScreen()
{
    // Check for events to handle
    glfwPollEvents();

    // Update the screen by swapping buffers
    glfwSwapBuffers(window);
}

GLFWwindow* Window::getWindow(){
    return window;
}





