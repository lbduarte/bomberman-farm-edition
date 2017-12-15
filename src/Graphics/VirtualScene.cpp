#include "VirtualScene.h"

#define M_PI 3.141592

using namespace Graphics;
using namespace VirtualScene;

void VirtualScene::init(Loader loader)
{
    //Create cow
    ObjModel obj("../../data/cow.obj");
    obj.computeNormals();
    obj.buildTriangles();
    cow = loader.loadObjToVAO(obj);
    cow_angleY = 0;

    //Create plan
    ObjModel obj2("../../data/plane.obj");
    obj2.computeNormals();
    obj2.buildTriangles();
    plan = loader.loadObjToVAO(obj2);

    //Create bomb
    ObjModel obj3("../../data/bomb.obj");
    obj3.computeNormals();
    obj3.buildTriangles();
    bomb = loader.loadObjToVAO(obj3);

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

    cube = loader.loadToVAO(model_coefficients, indices);

    //Random positions
    srand (time(NULL));

    //Posi��es poss�veis no mapa
    int positions[96][2] = {{-5,-5}, {-5,-4}, {-5,-3}, {-5,-2}, {-5,-1}, {-5,0}, {-5,1}, {-5,2}, {-5,3}, {-5,4}, {-5,5},
                {-4,-5}, {-4,-3}, {-4,-1}, {-4,1}, {-4,3}, {-4,5},
                {-3,-5}, {-3,-4}, {-3,-3}, {-3,-2}, {-3,-1}, {-3,0}, {-3,1}, {-3,2}, {-3,3}, {-3,4}, {-3,5},
                {-2,-5}, {-2,-3}, {-2,-1}, {-2,1}, {-2,3}, {-2,5},
                {-1,-5}, {-1,-4}, {-1,-3}, {-1,-2}, {-1,-1}, {-1,0}, {-1,1}, {-1,2}, {-1,3}, {-1,4}, {-1,5},
                {0,-5}, {0,-3}, {0,-1}, {0,1}, {0,3}, {0,5},
                {1,-5}, {1,-4}, {1,-3}, {1,-2}, {1,-1}, {1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5},
                {2,-5}, {2,-3}, {2,-1}, {2,1}, {2,3}, {2,5},
                {3,-5}, {3,-4}, {3,-3}, {3,-2}, {3,-1}, {3,0}, {3,1}, {3,2}, {3,3},
                {4,-5}, {4,-3}, {4,-1}, {4,1}, {4,3},
                {5,-5}, {5,-4}, {5,-3}, {5,-2}, {5,-1}, {5,0}, {5,1}, {5,2}, {5,3}, {5,4}};

    // Posi��o da vaca
    int num_positions = sizeof(positions)/sizeof(positions[0]);
    int index = rand() % num_positions;
    cow_position[0] = positions[index][0];
    cow_position[1] = positions[index][1];

    for(int i=index;i<num_positions-1;i++){
        positions[i][0]=positions[i+1][0];
        positions[i][1]=positions[i+1][1];
    }
    num_positions--;

    //Posi��o dos cubos de palha
    for(int i = 0; i<num_cubes; i++){
        int index = rand() % num_positions; // escolhe posi��o aleat�ria
        random_positions[i][0] = positions[index][0];
        random_positions[i][1] = positions[index][1];
        for(int j=index;j<num_positions-1;j++){ //remove posi��o para os pr�ximos sorteios
            positions[j][0]=positions[j+1][0];
            positions[j][1]=positions[j+1][1];
        }
        num_positions--;
    }
}

void VirtualScene::drawObjects(GLint model_uniform, GLint object_id_uniform, Renderer renderer, bool drawCow)
{
    drawPlans(model_uniform, object_id_uniform, renderer);
    drawWoodCubes(model_uniform, object_id_uniform, renderer);
    drawHayCubes(model_uniform, object_id_uniform, renderer);

    if(drawCow)
    {
        float delta = 3.141592 / 32;
        if (Input::Keyboard::isKeyPressed(GLFW_KEY_RIGHT))
        {
            cow_angleY += delta;
        }
        else if (Input::Keyboard::isKeyPressed(GLFW_KEY_LEFT))
        {
            cow_angleY -= delta;
        }
        //desenha vaca
        glm::mat4 modelMatrix = Matrix_Translate((0+cow_position[1]),-1.65,(-2+cow_position[0]))*Matrix_Rotate_Y(cow_angleY)*Matrix_Scale(0.5,0.5,0.5);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, COW);
        renderer.render(cow);
    }
//        //desenha bomba
//        glm::mat4 modelMatrix =  Matrix_Translate(1,-1.82,-2)*Matrix_Rotate_Y(M_PI/4)*Matrix_Scale(0.02,0.02,0.02);
//        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//        glUniform1i(object_id_uniform, BOMB);
//        renderer.render(bomb);
}

void VirtualScene::drawPlans(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
        glm::mat4 modelMatrix;
        glm::vec4 plan_min = glm::vec4(-1.0f,0.0f,-1.0f,1.0f);
        glm::vec4 plan_max = glm::vec4(1.0f,0.0f,1.0f,1.0f);
        //direita
        modelMatrix = Matrix_Translate(5.5001,-1,-2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);
        wall_positions[0][0] = modelMatrix*plan_min;
        wall_positions[0][1] = modelMatrix*plan_max;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);

        //esquerda
        modelMatrix = Matrix_Translate(-5.5001,-1,-2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);
        wall_positions[1][0] = modelMatrix*plan_min;
        wall_positions[1][1] = modelMatrix*plan_max;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);

        //ch�o
        modelMatrix = Matrix_Translate(0,-2.001,-2)*Matrix_Scale(5.5001,1,5.5001);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, FLOOR);
        renderer.render(plan);

        //fundo
        modelMatrix = Matrix_Translate(0,-1,-7.5001)*Matrix_Rotate_Y(M_PI/2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);
        wall_positions[2][0] = modelMatrix*plan_min;
        wall_positions[2][1] = modelMatrix*plan_max;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);

        //frente
        modelMatrix = Matrix_Translate(0,-1,3.5001)*Matrix_Rotate_Y(M_PI/2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);
        wall_positions[3][0] = modelMatrix*plan_min;
        wall_positions[3][1] = modelMatrix*plan_max;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, WALL);
        renderer.render(plan);
}

void VirtualScene::drawWoodCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
    glm::mat4 modelMatrix;

    glm::vec4 box_min = glm::vec4(-0.5f,-0.5f,-0.5f,1.0f);
    glm::vec4 box_max = glm::vec4(0.5f,0.5f,0.5f,1.0f);
    int i = 0;
    while(i<5)
    {
        int j = 0;
        while(j<5)
        {
            modelMatrix = Matrix_Translate((0+j),-1.5,(-2+i));
            cubes_positions[-2+i][0+j][0] = modelMatrix*box_min;
            cubes_positions[-2+i][0+j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            modelMatrix = Matrix_Translate((0-j),-1.5,(-2+i));
            cubes_positions[-2+i][0-j][0] = modelMatrix*box_min;
            cubes_positions[-2+i][0-j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            modelMatrix = Matrix_Translate((0+j),-1.5,(-2-i));
            cubes_positions[-2-i][0+j][0] = modelMatrix*box_min;
            cubes_positions[-2-i][0+j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            modelMatrix = Matrix_Translate((0-j),-1.5,(-2-i));
            cubes_positions[-2-i][0-j][0] = modelMatrix*box_min;
            cubes_positions[-2-i][0-j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            j+=2;
        }
        i+=2;
    }
}

void VirtualScene::drawHayCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
    glm::mat4 modelMatrix;

    glm::vec4 box_min = glm::vec4(-0.5f,-0.5f,-0.5f,1.0f);
    glm::vec4 box_max = glm::vec4(0.5f,0.5f,0.5f,1.0f);

    int posx;
    int posz;
    for(int i=0;i<num_cubes;i++){
            posz = random_positions[i][0];
            posx = random_positions[i][1];
            modelMatrix = Matrix_Translate((0+posx),-1.5,(-2+posz));
            cubes_positions[5+posz][5+posx][0] = modelMatrix*box_min;
            cubes_positions[5+posz][5+posx][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, HAYCUBE);
            renderer.render(cube);
    }
}
