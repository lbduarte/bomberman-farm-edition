#include "VirtualScene.h"

#define M_PI 3.141592

using namespace Graphics;
using namespace VirtualScene;

void VirtualScene::init(Loader loader)
{

    //Create plan
    ObjModel obj("../../data/plane.obj");
    obj.computeNormals();
    obj.buildTriangles();
    RawModel model(loader.loadObjToVAO(obj));
    plan = model;

    //Create cube
    std::vector<GLfloat> model_coefficients = {
    // Vértices de um cubo
    //    X      Y     Z     W
        -0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 0
        -0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 1
         0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 2
         0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 3
        -0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 4
        -0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 5
         0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 6
         0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 7
    };

    std::vector<GLuint> indices = {
        0, 1, 2, // triângulo 1
        7, 6, 5, // triângulo 2
        3, 2, 6, // triângulo 3
        4, 0, 3, // triângulo 4
        4, 5, 1, // triângulo 5
        1, 5, 6, // triângulo 6
        0, 2, 3, // triângulo 7
        7, 5, 4, // triângulo 8
        3, 6, 7, // triângulo 9
        4, 3, 7, // triângulo 10
        4, 1, 0, // triângulo 11
        1, 6, 2, // triângulo 12
    };

    model = loader.loadToVAO(model_coefficients, indices);
    cube = model;
}

void VirtualScene::drawObjects(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
    drawPlans(model_uniform, object_id_uniform, renderer);
    drawWoodCubes(model_uniform, object_id_uniform, renderer);
}

void VirtualScene::drawPlans(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
        glm::mat4 modelMatrix;

        //direita
        modelMatrix = Matrix_Translate(10,-1,-2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,10);
        wall_models.push_back(modelMatrix);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);

        //esquerda
        modelMatrix = Matrix_Translate(-10,-1,-2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,10);
        wall_models.push_back(modelMatrix);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);

        //chão
        modelMatrix = Matrix_Translate(0,-2,-2)*Matrix_Scale(10,1,10);
        wall_models.push_back(modelMatrix);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, FLOOR);
        renderer.render(plan);

        //fundo
        modelMatrix = Matrix_Translate(0,-1,-12)*Matrix_Rotate_Y(M_PI/2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,10);
        wall_models.push_back(modelMatrix);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);

//        //frente
//        modelMatrix = Matrix_Translate(0,-1,8)*Matrix_Rotate_Y(M_PI/2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,10);
//        wall_models.push_back(modelMatrix);
//        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//        glUniform1i(object_id_uniform, PLAN);
//        renderer.render(model);
}

void VirtualScene::drawWoodCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
        glm::mat4 modelMatrix;

        //direita
        modelMatrix = Matrix_Translate(0,-1,-2);
        wood_cube_models.push_back(modelMatrix);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, CUBE);
        renderer.render(cube);

}

