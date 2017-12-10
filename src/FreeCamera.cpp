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
    incVector = 0.05f * viewVector;

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

