#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include "RawModel.h"
#include "ObjModel.h"
#include "AttributeLocation.h"
#include <iostream>
#include <cstdio>

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
            RawModel loadObjToVAO(ObjModel object);
            void cleanUp();

        private:
            GLuint createVAO();
            void storeDataInAttributeList(AttributeLocation location, int number_of_dimensions, std::vector<GLfloat> data);
            void bindIndicesBuffer(std::vector<GLuint> data);
            void unbindVAO();
    };
}

#endif // LOADER_H
