#include "Projection.h"

using namespace Projection;

void Projection::init()
{
    nearplane = -0.1f;
    farplane = -10.0f;
    field_of_view = 3.141592 / 3.0f;
}

void Projection::computeProjectionMatrix()
{
    projectionMatrix = Matrix_Perspective(field_of_view, Graphics::Window::getScreenRatio(), nearplane, farplane);
}

glm::mat4 Projection::getProjectionMatrix()
{
    return projectionMatrix;
}

float Projection::getNearPlane()
{
    return nearplane;
}

float Projection::getFarPlane()
{
    return farplane;
}

float Projection::getFieldOfView()
{
    return field_of_view;
}
