#include "FreeCamera.h"

using namespace Cameras;
using namespace Free;

void Free::init(float a_theta, float a_phi, float a_distance, glm::vec4 camera_position_c, glm::vec4 camera_view_vector)
{
    theta = a_theta;
    phi = a_phi;
    distance = a_distance;
    viewVector = camera_view_vector;
    position_C = camera_position_c;
    upVector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    bottomNearLeft = glm::vec4(position_C.x - 0.25f, position_C.y - 0.25f, position_C.z + 0.25f, 0.0f);
    topFarRight = glm::vec4(position_C.x + 0.25f, position_C.y + 0.25f, position_C.z - 0.25f, 0.0f);
    movementVector = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void Free::updateCamera()
{
    r = distance;
    y = r * sin(phi);
    z = r * cos(phi) * cos(theta);
    x = r * cos(phi) * sin(theta);
    incVector = 0.03f * viewVector;
    incVector.y = 0;

    movementVector = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_D))
        movementVector -= crossproduct(upVector, incVector);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_A))
        movementVector += crossproduct(upVector, incVector);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_W))
        movementVector += incVector;

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_S))
        movementVector -= incVector;

    glm::vec4 newPosition = Graphics::VirtualScene::checkCollision(position_C, movementVector);

    position_C = newPosition;

    updateBoundingBox(position_C);


    viewVector = glm::vec4(x, y, z, 0.0f);
}

void Free::computeViewMatrix()
{
    viewMatrix = Matrix_Camera_View(position_C, viewVector, upVector);
}

glm::mat4 Free::getViewMatrix()
{
    return viewMatrix;
}

float Free::getTheta()
{
    return theta;
}

float Free::getPhi()
{
    return phi;
}

float Free::getDistance()
{
    return distance;
}

void Free::updateTheta(float dx)
{
    theta -= 0.01f*dx;
}

void Free::updatePhi(float dy)
{
    phi += 0.01f*dy;

    float phimax = 3.141592f/2;
    float phimin = -phimax;

    if (phi > phimax)
        phi = phimax;

    if (phi < phimin)
        phi = phimin;
}

void Free::updateDistance(double yoffset)
{
    distance -= 0.1f*yoffset;

    if (distance < 0.0f)
        distance = 0.0f;
}

glm::vec4 Free::getPosition()
{
    return position_C;
}

glm::vec4 Free::getIncVector()
{
    return incVector;
}

glm::vec4 Free::getUpVector()
{
    return upVector;
}

glm::vec4 Free::getBottomNearLeft()
{
    return bottomNearLeft;
}

glm::vec4 Free::getTopFarRight()
{
    return topFarRight;
}

void Free::updateBoundingBox(glm::vec4 position)
{
    bottomNearLeft = glm::vec4(position.x - 0.25f, position.y - 0.25f, position.z + 0.25f, 0.0f);
    topFarRight = glm::vec4(position.x + 0.25f, position.y + 0.25f, position.z - 0.25f, 0.0f);
}

