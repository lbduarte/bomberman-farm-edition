#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream>
#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Keyboard.h"
#include "Mouse.h"

namespace Graphics
{
    namespace Window
    {
        static GLFWwindow *window;
        static const char *title;
        static int width;
        static int height;
        static float screenRatio;

        void create(const char* p_title, int p_width, int p_height);
        bool init();
        void destroy();
        void updateScreen();
        void clearBuffer();
        bool shouldClose();
        int getWidth();
        int getHeight();
        float getScreenRatio();
        const char* getTitle();

        // Window Callbacks
        void frameBufferSizeCallback(GLFWwindow* p_window, int p_width, int p_height);
    }
}
#endif // WINDOW_H_INCLUDED

