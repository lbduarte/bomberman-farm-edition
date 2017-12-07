#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include "RawModel.h"

namespace Graphics
{

    class Loader
    {
        private:
            std::vector<GLuint> vaos;
            std::vector<GLuint> vbos;
        public:
            Loader();
            ~Loader();
            RawModel loadToVAO(GLfloat* positions);
            void cleanUp();

        private:
            GLuint createVAO();
            void storeDataInAttributeList(int attributeNumber,GLfloat* data);
            void unbindVAO();
    };
}

#endif // LOADER_H
