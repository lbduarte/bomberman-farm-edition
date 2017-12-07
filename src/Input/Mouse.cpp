#include "Mouse.h"

using namespace Input;
using namespace Mouse;

void Mouse::init()
{
    cursorX = 0.0;
    cursorY = 0.0;

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
}

void Mouse::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    //TODO
}
