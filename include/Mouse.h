#ifndef MOUSE_H
#define MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Input
{
    namespace Mouse
    {
        #define MAX_BUTTONS 100

        static bool mouseButtons[MAX_BUTTONS];

        // Cursor position relative to the window
        static double cursorX;
        static double cursorY;

        void init();
        bool isMouseButtonPressed(int buttonCode);
        void getCursorPosition(double &x, double &y);

        // Mouse Callbacks
        void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    }
}
#endif // MOUSE_H
