#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include "RawModel.h"
#include "ObjModel.h"
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
            RawModel loadToVAO(std::vector<GLfloat> model_coefficients, std::vector<GLuint> indices, std::vector<GLfloat> color_coefficients);
            void cleanUp();

        private:
            enum Location {
                POSITION,
                COLOR
            };
            GLuint createVAO();
            void storeDataInAttributeList(Location location, std::vector<GLfloat> data);
            void bindIndicesBuffer(std::vector<GLuint> data);
            void unbindVAO();
    };
}

#endif // LOADER_H
