#include "LookAtCamera.h"

LookAtCamera::LookAtCamera(float theta, float phi, float distance, glm::vec4 lookat_point)
{
    m_Theta = theta;
    m_Phi = phi;
    m_Distance = distance;
    m_LookAt_L = lookat_point;
    m_Up_Vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

LookAtCamera::~LookAtCamera()
{

}

void LookAtCamera::computePosition()
{
    r = m_Distance;
    y = r * sin(m_Phi);
    z = r * cos(m_Phi) * cos(m_Theta);
    x = r * cos(m_Phi) * sin(m_Theta);
    m_Position_C = glm::vec4(x, y, z, 1.0f);
    m_View_Vector = m_LookAt_L - m_Position_C;
}

void LookAtCamera::computeView()
{
    m_View_Matrix = Matrix_Camera_View(m_Position_C, m_View_Vector, m_Up_Vector);
}

glm::mat4 LookAtCamera::getViewMatrix()
{
    return m_View_Matrix;
}

float LookAtCamera::getTheta()
{
    return m_Theta;
}

float LookAtCamera::getPhi()
{
    return m_Phi;
}

float LookAtCamera::getDistance()
{
    return m_Distance;
}
