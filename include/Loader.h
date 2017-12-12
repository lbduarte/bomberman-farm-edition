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
#include <stb_image.h>

namespace Graphics
{

    class Loader
    {
        private:
            std::vector<GLuint> vaos;
            std::vector<GLuint> vbos;
            int g_NumLoadedTextures;
        public:
            Loader();
            ~Loader();
            RawModel loadToVAO(std::vector<GLfloat> model_coefficients, std::vector<GLuint> indices);
            RawModel loadObjToVAO(ObjModel object);
            void cleanUp();
            void loadTextureImage(const char* filename);
            int getNumTextures();

        private:
            GLuint createVAO();
            void storeDataInAttributeList(AttributeLocation location, int number_of_dimensions, std::vector<GLfloat> data);
            void bindIndicesBuffer(std::vector<GLuint> data);
            void unbindVAO();
    };
}

#endif // LOADER_H
