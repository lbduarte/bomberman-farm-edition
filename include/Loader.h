#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include "RawModel.h"
#include <iostream>

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
            RawModel loadToVAO(std::vector<GLfloat> positions, std::vector<GLuint> indices);
            void cleanUp();

        private:
            GLuint createVAO();
            void storeDataInAttributeList(int attributeNumber, std::vector<GLfloat> data);
            void bindIndicesBuffer(std::vector<GLuint> data);
            void unbindVAO();
    };
}

#endif // LOADER_H
