#include "Keyboard.h"

using namespace Input;
using namespace Keyboard;


void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keys[key] = action != GLFW_RELEASE;
}

void Keyboard::init()
{
    for (int i=0; i < MAX_KEYS; i++)
    {
        keys[i] = false;
    }
}

bool Keyboard::isKeyPressed(int keycode)
{
    if (keycode >= MAX_KEYS)
    {
        //TODO Log this
        return false;
    }

    return keys[keycode];
}

