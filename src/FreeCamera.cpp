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
}

void Free::computePosition()
{
    r = distance;
    y = r * sin(phi);
    z = r * cos(phi) * cos(theta);
    x = r * cos(phi) * sin(theta);
    incVector = 0.03f * viewVector;

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_D))
        position_C -= crossproduct(upVector, incVector);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_A))
        position_C += crossproduct(upVector, incVector);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_W))
        position_C += incVector;

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_S))
        position_C -= incVector;

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
    phi += 0.01f*-dy;

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
