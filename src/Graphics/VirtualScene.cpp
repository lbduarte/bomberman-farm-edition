#include "VirtualScene.h"
#include "ObjModel.h"
#include "RawModel.h"
#include "matrices.h"
#include "Loader.h"
#include "ObjectId.h"
#include "Renderer.h"

#define M_PI 3.141592

using namespace Graphics;
using namespace VirtualScene;

void VirtualScene::init()
{

    Graphics::Loader loader;

    //Create plan
    ObjModel obj("../../data/plane.obj");
    obj.computeNormals();
    obj.buildTriangles();
    RawModel model(loader.loadObjToVAO(obj));

    plan = model;

    //Create cube
//    std::vector<GLfloat> model_coefficients = {
//    // V�rtices de um cubo
//    //    X      Y     Z     W
//        -0.5f,  0.5f,  0.5f, 1.0f, // posi��o do v�rtice 0
//        -0.5f, -0.5f,  0.5f, 1.0f, // posi��o do v�rtice 1
//         0.5f, -0.5f,  0.5f, 1.0f, // posi��o do v�rtice 2
//         0.5f,  0.5f,  0.5f, 1.0f, // posi��o do v�rtice 3
//        -0.5f,  0.5f, -0.5f, 1.0f, // posi��o do v�rtice 4
//        -0.5f, -0.5f, -0.5f, 1.0f, // posi��o do v�rtice 5
//         0.5f, -0.5f, -0.5f, 1.0f, // posi��o do v�rtice 6
//         0.5f,  0.5f, -0.5f, 1.0f, // posi��o do v�rtice 7
//    };
//
//    std::vector<GLuint> indices = {
//        0, 1, 2, // tri�ngulo 1
//        7, 6, 5, // tri�ngulo 2
//        3, 2, 6, // tri�ngulo 3
//        4, 0, 3, // tri�ngulo 4
//        4, 5, 1, // tri�ngulo 5
//        1, 5, 6, // tri�ngulo 6
//        0, 2, 3, // tri�ngulo 7
//        7, 5, 4, // tri�ngulo 8
//        3, 6, 7, // tri�ngulo 9
//        4, 3, 7, // tri�ngulo 10
//        4, 1, 0, // tri�ngulo 11
//        1, 6, 2, // tri�ngulo 12
//    };
//
//    std::vector<GLfloat> color_coefficients = {
//    // Cores dos v�rtices do cubo
//    //  R     G     B     A
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do v�rtice 0
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do v�rtice 1
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do v�rtice 2
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do v�rtice 3
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do v�rtice 4
//        1.0f, 0.5f, 0.0f, 1.0f, // cor do v�rtice 5
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do v�rtice 6
//        0.0f, 0.5f, 1.0f, 1.0f, // cor do v�rtice 7
//    };

//    RawModel model = loader.loadToVAO(model_coefficients, indices, color_coefficients);
//    glUniform1i(object_id_uniform, CUBE);
    //this->cube = model;
}

void VirtualScene::drawObjects(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
        glm::mat4 modelMatrix;

        modelMatrix = Matrix_Translate(0,-2,0)*Matrix_Scale(5,0,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLAN);
        renderer.render(plan);

        modelMatrix = Matrix_Translate(2.5,-2,0)*Matrix_Rotate_Y(M_PI/2)*Matrix_Scale(2,0,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLAN);
        renderer.render(plan);

        modelMatrix = Matrix_Translate(-2.5,-2,0)*Matrix_Rotate_Y(M_PI/2)*Matrix_Scale(2,0,5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, PLAN);
        renderer.render(plan);
}

