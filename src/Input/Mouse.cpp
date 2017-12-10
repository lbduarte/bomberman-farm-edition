#include "Mouse.h"

using namespace Input;
using namespace Mouse;

void Mouse::init()
{
    cursorX = 0.0;
    cursorY = 0.0;
    lastCursorX = 0.0;
    lastCursorY = 0.0;

    for (int i=0; i < MAX_BUTTONS; i++)
    {
        mouseButtons[i] = false;
    }
}

bool isMouseButtonPressed(int buttonCode)
{
    if (buttonCode >= MAX_BUTTONS)
    {
        // TODO Log this
        return false;
    }

    return mouseButtons[buttonCode];
}

void Mouse::getCursorPosition(double &x, double &y)
{
    x = cursorX;
    y = cursorY;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    mouseButtons[button] = action != GLFW_RELEASE;
}

void Mouse::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    cursorX = xpos;
    cursorY = ypos;

    float dx = xpos - lastCursorX;
    float dy = ypos - lastCursorY;


    Cameras::LookAt::theta -= 0.01f*dx;
    Cameras::LookAt::phi += 0.01f*dy;

    Cameras::Free::theta -= 0.01f*dx;
    Cameras::Free::phi += 0.01f*-dy;

    float phimax = 3.141592f/2;
    float phimin = -phimax;

    if (Cameras::LookAt::phi > phimax)
        Cameras::LookAt::phi = phimax;

    if (Cameras::LookAt::phi < phimin)
        Cameras::LookAt::phi = phimin;

    if (Cameras::Free::phi > phimax)
        Cameras::Free::phi = phimax;

    if (Cameras::Free::phi < phimin)
        Cameras::Free::phi = phimin;

    lastCursorX = xpos;
    lastCursorY = ypos;
}

void Mouse::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Cameras::LookAt::distance -= 0.1f*yoffset;

    if (Cameras::LookAt::distance < 0.0f)
        Cameras::LookAt::distance = 0.0f;
}
