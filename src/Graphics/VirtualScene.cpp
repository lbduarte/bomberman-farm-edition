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
    std::vector<GLfloat> model_coefficients =
    {
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

    std::vector<GLuint> indices =
    {
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

    // Initializes array
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            for (int k = 0; k < 2; k++)
                cubes_positions[i][j][k] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    //Posi��es poss�veis no mapa {z,x}
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
        {5,-5}, {5,-4}, {5,-3}, {5,-2}, {5,-1}, {5,0}, {5,1}, {5,2}, {5,3}, {5,4}
    };

    // Posi��o da vaca
    int num_positions = sizeof(positions)/sizeof(positions[0]);
    int index = rand() % num_positions;
    cow_position[0] = positions[index][0];
    cow_position[1] = positions[index][1];

    for(int i=index; i<num_positions-1; i++)
    {
        positions[i][0]=positions[i+1][0];
        positions[i][1]=positions[i+1][1];
    }
    num_positions--;

    // inicializa ids com -1
    for(int i =0;i<11;i++)
        for(int j =0;j<11;j++)
            hay_cubes_ids[i][j] = -1;

    //Posi��o dos cubos de palha
    for(int i = 0; i<num_cubes; i++)
    {
        int index = rand() % num_positions; // escolhe posi��o aleat�ria
        random_positions[i][0] = positions[index][0];
        random_positions[i][1] = positions[index][1];
        hay_cubes_ids[5+positions[index][0]][5+positions[index][1]] = i;
        for(int j=index; j<num_positions-1; j++) //remove posi��o para os pr�ximos sorteios
        {
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
}

void VirtualScene::drawPlans(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
    glm::mat4 modelMatrix;
    glm::vec4 plan_min = glm::vec4(-1.0f,0.0f,1.0f,1.0f);
    glm::vec4 plan_max_dir = glm::vec4(1.0f,-0.2f,-1.0f,1.0f);
    glm::vec4 plan_max_esq = glm::vec4(1.0f,-0.2f,-1.0f,1.0f);
    glm::vec4 plan_max_fre = glm::vec4(1.0f,0.0f,0.0f,1.0f);
    glm::vec4 plan_max_tras = glm::vec4(1.0f,0.0f,-1.0f,1.0f);

    //direita
    modelMatrix = Matrix_Translate(5.5001,-1,-2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);

    wall_positions[0][0] = modelMatrix*plan_min;
    wall_positions[0][1] = modelMatrix*plan_max_dir;
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform1i(object_id_uniform, WALL);
    renderer.render(plan);

    //esquerda
    modelMatrix = Matrix_Translate(-5.5001,-1,-2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);
    wall_positions[1][0] = modelMatrix*plan_min;
    wall_positions[1][1] = modelMatrix*plan_max_esq;
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
    wall_positions[2][1] = modelMatrix*plan_max_tras;
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform1i(object_id_uniform, WALL);
    renderer.render(plan);

    //frente
    modelMatrix = Matrix_Translate(0,-1,3.5001)*Matrix_Rotate_Y(M_PI/2)*Matrix_Rotate_Z(M_PI/2)*Matrix_Scale(1,1,5.5001);
    wall_positions[3][0] = modelMatrix*plan_min;
    wall_positions[3][1] = modelMatrix*plan_max_fre;
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform1i(object_id_uniform, WALL);
    renderer.render(plan);

}

void VirtualScene::drawWoodCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer)
{
    glm::mat4 modelMatrix;

    glm::vec4 box_min = glm::vec4(-0.5f,-0.5f,0.5f,1.0f);
    glm::vec4 box_max = glm::vec4(0.5f,0.5f,-0.5f,1.0f);
    int i = 0;
    while(i<5)
    {
        int j = 0;
        while(j<5)
        {
            modelMatrix = Matrix_Translate((0+j),-1.5,(-2+i));
            cubes_positions[5+i][5+j][0] = modelMatrix*box_min;
            cubes_positions[5+i][5+j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            modelMatrix = Matrix_Translate((0-j),-1.5,(-2+i));
            cubes_positions[5+i][5-j][0] = modelMatrix*box_min;
            cubes_positions[5+i][5-j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            modelMatrix = Matrix_Translate((0+j),-1.5,(-2-i));
            cubes_positions[5-i][5+j][0] = modelMatrix*box_min;
            cubes_positions[5-i][5+j][1] = modelMatrix*box_max;
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniform1i(object_id_uniform, WOODCUBE);
            renderer.render(cube);

            modelMatrix = Matrix_Translate((0-j),-1.5,(-2-i));
            cubes_positions[5-i][5-j][0] = modelMatrix*box_min;
            cubes_positions[5-i][5-j][1] = modelMatrix*box_max;
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

    glm::vec4 box_min = glm::vec4(-0.5f,-0.5f,0.5f,1.0f);
    glm::vec4 box_max = glm::vec4(0.5f,0.5f,-0.5f,1.0f);

    int posx;
    int posz;
    for(int i=0; i<num_cubes; i++)
    {
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

void VirtualScene::drawBomb(GLint model_uniform, GLint object_id_uniform, Renderer renderer, glm::vec4 position)
{
        //desenha bomba
        bomb_position[0] = 2+roundf(position.z);
        bomb_position[1] = roundf(position.x);

        glm::mat4 modelMatrix =  Matrix_Translate(bomb_position[1],-1.82,-2+bomb_position[0])*Matrix_Rotate_Y(M_PI/4)*Matrix_Scale(0.02,0.02,0.02);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform1i(object_id_uniform, BOMB);
        renderer.render(bomb);
}

int VirtualScene::getCowPositionX()
{
    return cow_position[1];
}

int VirtualScene::getCowPositionZ()
{
    return cow_position[0];
}
void VirtualScene::explode()
{
    int bombX = bomb_position[1];
    int bombZ = bomb_position[0];
    int index;

    if(bombX!=5){
        //remove um para direita

        index = hay_cubes_ids[5+bombZ][5+bombX+1];
        if(index != -1){
            for(int j=index; j<num_cubes-1; j++) //remove cubo
            {
                random_positions[j][0]=random_positions[j+1][0];
                random_positions[j][1]=random_positions[j+1][1];
            }
            num_cubes--;
            hay_cubes_ids[5+bombZ][5+bombX+1] = -1;
            for(int i =0;i<11;i++)
                for(int j =0;j<11;j++){
                    if(hay_cubes_ids[i][j]>index)
                        hay_cubes_ids[i][j]--;
                }
        }
        cubes_positions[5+bombZ][5+bombX+1][0]=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        cubes_positions[5+bombZ][5+bombX+1][1]=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    if(bombX!=-5){
        //remove um para esquerda
        index = hay_cubes_ids[5+bombZ][5+bombX-1];
        if(index != -1){
            for(int j=index; j<num_cubes-1; j++) //remove cubo
            {
                random_positions[j][0]=random_positions[j+1][0];
                random_positions[j][1]=random_positions[j+1][1];
            }
            num_cubes--;
            hay_cubes_ids[5+bombZ][5+bombX-1] = -1;
            for(int i =0;i<11;i++)
                for(int j =0;j<11;j++){
                    if(hay_cubes_ids[i][j]>index)
                        hay_cubes_ids[i][j]--;
                }
        }
        cubes_positions[5+bombZ][5+bombX-1][0]=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        cubes_positions[5+bombZ][5+bombX-1][1]=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    if(bombZ!=5){
        //remove um para tr�s
        index = hay_cubes_ids[5+bombZ+1][5+bombX];
        if(index != -1){
            for(int j=index; j<num_cubes-1; j++) //remove cubo
            {
                random_positions[j][0]=random_positions[j+1][0];
                random_positions[j][1]=random_positions[j+1][1];
            }
            num_cubes--;
            hay_cubes_ids[5+bombZ+1][5+bombX] = -1;
            for(int i =0;i<11;i++)
                for(int j =0;j<11;j++){
                    if(hay_cubes_ids[i][j]>index)
                        hay_cubes_ids[i][j]--;
                }
        }
        cubes_positions[5+bombZ+1][5+bombX][0]=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        cubes_positions[5+bombZ+1][5+bombX][1]=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    if(bombZ!=-5){
        //remove um para frente
        index = hay_cubes_ids[5+bombZ-1][5+bombX];
        if(index != -1){
            for(int j=index; j<num_cubes-1; j++) //remove cubo
            {
                random_positions[j][0]=random_positions[j+1][0];
                random_positions[j][1]=random_positions[j+1][1];
            }
            num_cubes--;
            hay_cubes_ids[5+bombZ-1][5+bombX] = -1;
            for(int i =0;i<11;i++)
                for(int j =0;j<11;j++){
                    if(hay_cubes_ids[i][j]>index)
                        hay_cubes_ids[i][j]--;
                }
        }
        cubes_positions[5+bombZ-1][5+bombX][0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        cubes_positions[5+bombZ-1][5+bombX][1] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}

glm::vec4 VirtualScene::checkCollision(glm::vec4 oldPosition, glm::vec4 movementVector)
{
    glm::vec4 newPosition = oldPosition + movementVector;

    Cameras::Free::updateBoundingBox(newPosition);

        for (int i = 0; i < 11; i++)
            for (int j = 0; j < 11; j++)
            {
                if(cubes_positions[i][j][0] == glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) && cubes_positions[i][j][1] == glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
                {
                    //std::cout << "i = " << i << " j = " << j << std::endl;
                    //std::cin.get();
                    // N�o precisa testar pq nao tem cubo nessa posi��o
                }
                else
                {
                    //std::cout << "COLIDIU!!!" << std::endl;
                    // Tem cubo aqui entao testa colisao
                    if (collided(cubes_positions[i][j][0], cubes_positions[i][j][1]))
                    {
                        return oldPosition;
                    }

                }
            }

        for (int i = 0; i < 4; i++)
        {
            //std::cout << wall_positions[i][0].x << " " << wall_positions[i][1].x << std::endl;
            //std::cin.get();
            if (collidedWithPlane(wall_positions[i][0], wall_positions[i][1], newPosition))
            {
                return oldPosition;
            }
        }

    return oldPosition + movementVector;
}

bool VirtualScene::collided(glm::vec4 bottomNearLeft, glm::vec4 topFarRight)
{
  return (Cameras::Free::getBottomNearLeft().x <= topFarRight.x && Cameras::Free::getTopFarRight().x >= bottomNearLeft.x) &&
         (Cameras::Free::getBottomNearLeft().y <= topFarRight.y && Cameras::Free::getTopFarRight().y >= bottomNearLeft.y) &&
         (Cameras::Free::getBottomNearLeft().z >= topFarRight.z && Cameras::Free::getTopFarRight().z <= bottomNearLeft.z);
}

bool VirtualScene::collidedWithPlane(glm::vec4 plan_min, glm::vec4 plan_max, glm::vec4 newPosition)
{

  return (newPosition.x <= plan_max.x && newPosition.x >= plan_min.x) &&
         (newPosition.y <= plan_max.y && newPosition.y >= plan_min.y) &&
         (newPosition.z >= plan_max.z && newPosition.z <= plan_min.z);
}

