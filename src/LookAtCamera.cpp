#include "LookAtCamera.h"

using namespace Cameras;
using namespace LookAt;

void LookAt::init(float a_theta, float a_phi, float a_distance, glm::vec4 lookat_point)
{
    theta = a_theta;
    phi = a_phi;
    distance = a_distance;
    lookAt_L = lookat_point;
    upVector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

void LookAt::computePosition()
{
    r = distance;
    y = r * sin(phi);
    z = r * cos(phi) * cos(theta);
    x = r * cos(phi) * sin(theta);
    position_C = glm::vec4(x, y, z, 1.0f);
    viewVector = lookAt_L - position_C;

}

void LookAt::computeViewMatrix()
{
    viewMatrix = Matrix_Camera_View(position_C, viewVector, upVector);
}

glm::mat4 LookAt::getViewMatrix()
{
    return viewMatrix;
}

float LookAt::getTheta()
{
    return theta;
}

float LookAt::getPhi()
{
    return phi;
}

float LookAt::getDistance()
{
    return distance;
}

void LookAt::updateTheta(float dx)
{
    theta -= 0.01f*dx;
}

void LookAt::updatePhi(float dy)
{
    phi += 0.01f*dy;

    float phimax = 3.141592f/2;
    float phimin = -phimax;

    if (phi > phimax)
        phi = phimax;

    if (phi < phimin)
        phi = phimin;
}

void LookAt::updateDistance(double yoffset)
{
    distance -= 0.1f*yoffset;

    if (distance < 0.0f)
        distance = 0.0f;
}


