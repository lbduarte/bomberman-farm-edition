#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include "RawModel.h"

namespace Graphics
{

    class Renderer
    {
        public:
            Renderer();
            ~Renderer();
            void prepare();
            void render(RawModel model);
        private:
    };
}

#endif // RENDERER_H
