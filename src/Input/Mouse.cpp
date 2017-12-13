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


    getCursorPosition(lastCursorX, lastCursorY);
}

void Mouse::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    cursorX = xpos;
    cursorY = ypos;

    if (!mouseButtons[GLFW_MOUSE_BUTTON_LEFT])
        return;

    float dx = xpos - lastCursorX;
    float dy = ypos - lastCursorY;

    Cameras::LookAt::updateTheta(dx);
    Cameras::LookAt::updatePhi(dy);

    Cameras::Free::updateTheta(dx);
    Cameras::Free::updatePhi(dy);

    lastCursorX = xpos;
    lastCursorY = ypos;
}

void Mouse::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Cameras::LookAt::updateDistance(yoffset);
}

