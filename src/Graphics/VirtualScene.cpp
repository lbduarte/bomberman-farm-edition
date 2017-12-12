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
    // V�rtices de um cubo
    //    X      Y     Z     W
        -0.5f,  0.5f,  0.5f, 1.0f, // posi��o do v�rtice 0
        -0.5f, -0.5f,  0.5f, 1.0f, // posi��o do v�rtice 1
         0.5f, -0.5f,  0.5f, 1.0f, // posi��o do v�rtice 2
         0.5f,  0.5f,  0.5f, 1.0f, // posi��o do v�rtice 3
        -0.5f,  0.5f, -0.5f, 1.0f, // posi��o do v�rtice 4
        -0.5f, -0.5f, -0.5f, 1.0f, // posi��o do v�rtice 5
         0.5f, -0.5f, -0.5f, 1.0f, // posi��o do v�rtice 6
         0.5f,  0.5f, -0.5f, 1.0f, // posi��o do v�rtice 7
    };

    std::vector<GLuint> indices = {
        0, 1, 2, // tri�ngulo 1
        7, 6, 5, // tri�ngulo 2
        3, 2, 6, // tri�ngulo 3
        4, 0, 3, // tri�ngulo 4
        4, 5, 1, // tri�ngulo 5
        1, 5, 6, // tri�ngulo 6
        0, 2, 3, // tri�ngulo 7
        7, 5, 4, // tri�ngulo 8
        3, 6, 7, // tri�ngulo 9
        4, 3, 7, // tri�ngulo 10
        4, 1, 0, // tri�ngulo 11
        1, 6, 2, // tri�ngulo 12
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

        //ch�o
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

