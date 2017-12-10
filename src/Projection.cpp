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
    projectionMatrix = Matrix_Perspective(field_of_view, Graphics::Window::screenRatio, nearplane, farplane);
}
