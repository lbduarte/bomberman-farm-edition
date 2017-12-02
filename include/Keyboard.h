#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Keyboard
{
    #define MAX_KEYS 500

    static bool keys[MAX_KEYS];

    void init();
    bool isKeyPressed(int keycode);

    // Keyboard Callbacks
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif // KEYBOARD_H
