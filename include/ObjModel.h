#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Headers da biblioteca para carregar modelos obj
#include <tiny_obj_loader.h>

#include <glm/vec4.hpp>
#include <matrices.h>


namespace Graphics
{
    class ObjModel
    {
        private:
            tinyobj::attrib_t                 attrib;
            std::vector<tinyobj::shape_t>     shapes;
            std::vector<tinyobj::material_t>  materials;
            std::vector<GLuint> indices;
            std::vector<float>  model_coefficients;
            std::vector<float>  normal_coefficients;
            std::vector<float>  texture_coefficients;
        public:
            ObjModel(const char* filename, const char* basepath = NULL, bool triangulate = true);
            void computeNormals();
            void buildTriangles();
            std::vector<GLuint> getIndices();
            std::vector<float> getModelCoefficients();
            std::vector<float> getNormalCoefficients();
            std::vector<float> getTextureCoefficients();
        private:
    };
}

#endif // OBJMODEL_H
