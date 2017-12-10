#include "FreeCamera.h"

FreeCamera::FreeCamera(float theta, float phi, float distance, glm::vec4 camera_position_c, glm::vec4 camera_view_vector)
{
    m_Theta = theta;
    m_Phi = phi;
    m_Distance = distance;
    m_View_Vector = camera_view_vector;
    m_Position_C = camera_position_c;
    m_Up_Vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

FreeCamera::~FreeCamera()
{
    //dtor
}

void FreeCamera::computePosition()
{
    r = m_Distance;
    y = r * sin(m_Phi);
    z = r * cos(m_Phi) * cos(m_Theta);
    x = r * cos(m_Phi) * sin(m_Theta);
    m_Inc_Vector = 0.05f * m_View_Vector;

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_D))
        m_Position_C -= crossproduct(m_Up_Vector, m_Inc_Vector);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_A))
        m_Position_C += crossproduct(m_Up_Vector, m_Inc_Vector);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_W))
        m_Position_C += m_Inc_Vector;

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_S))
        m_Position_C -= m_Inc_Vector;

    m_View_Vector = glm::vec4(x, y, z, 0.0f);
}

void FreeCamera::computeView()
{
    m_View_Matrix = Matrix_Camera_View(m_Position_C, m_View_Vector, m_Up_Vector);
}

glm::mat4 FreeCamera::getViewMatrix()
{
    return m_View_Matrix;
}

float FreeCamera::getTheta()
{
    return m_Theta;
}

float FreeCamera::getPhi()
{
    return m_Phi;
}

float FreeCamera::getDistance()
{
    return m_Distance;
}
