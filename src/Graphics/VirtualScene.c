#include "VirtualScene.h"
#include "ObjModel.h"
#include "RawModel.h"
#include "matrices.h"

#define M_PI 3.141592

using namespace Graphics;

void VirtualScene::createObjects(){

    //Create plan
    ObjModel obj("../../data/plane.obj");
    obj.computeNormals();
    obj.buildTriangles();
    RawModel model = loader.loadObjToVAO(obj);

    //Create cube


//    Graphics::RawModel model = loader.loadToVAO(model_coefficients, indices, color_coefficients);
//    glUniform1i(object_id_uniform, CUBE);
//    std::vector<GLfloat> model_coefficients = {
//    // Vértices de um cubo
//    //    X      Y     Z     W
//        -0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 0
//        -0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 1
//         0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 2
//         0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 3
//        -0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 4
//        -0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 5
//         0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 6
//         0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 7
//    };
//
//    std::vector<GLuint> indices = {
//        0, 1, 2, // triângulo 1
//        7, 6, 5, // triângulo 2
//        3, 2, 6, // triângulo 3
//        4, 0, 3, // triângulo 4
//        4, 5, 1, // triângulo 5
//        1, 5, 6, // triângulo 6
//        0, 2, 3, // triângulo 7
//        7, 5, 4, // triângulo 8
//        3, 6, 7, // triângulo 9
//        4, 3, 7, // triângulo 10
//        4, 1, 0, // triângulo 11
//        1, 6, 2, // triângulo 12
//    };
//
//    std::vector<GLfloat> color_coefficients = {
//    // Cores dos vértices do cubo
//    //  R     G     B     A
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 0
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 1
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 2
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 3
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 4
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 5
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 6
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 7
//    };
}

void VirtualScene::DrawObjects(GLint model_uniform){

        modelMatrix = Matrix_Translate(0,-2,0)*Matrix_Scale(5,0,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLANE);
        renderer.render(this->plan);

        modelMatrix = Matrix_Translate(2.5,-2,0)*Matrix_Rotate_Y(M_PI/2)*Matrix_Scale(2,0,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLANE);
        renderer.render(this->plan);

        modelMatrix = Matrix_Translate(-2.5,-2,0)*Matrix_Rotate_Y(M_PI/2)*Matrix_Scale(2,0,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLANE);
        renderer.render(this->plan);

        modelMatrix = Matrix_Translate(0,-2,0)*Matrix_Scale(5,5,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLANE);
        renderer.render(this->plan);
}
