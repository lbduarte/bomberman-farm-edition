#ifndef FREECAMERA_H
#define FREECAMERA_H

#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "matrices.h"
#include "Keyboard.h"

class FreeCamera
{
    private:
        float m_Theta;
        float m_Phi;
        float m_Distance;
        float r;
        float y;
        float z;
        float x;
        glm::vec4 m_Position_C;
        glm::vec4 m_Inc_Vector;
        glm::vec4 m_View_Vector;
        glm::vec4 m_Up_Vector;
        glm::mat4 m_View_Matrix;

    public:
        FreeCamera(float theta, float phi, float distance, glm::vec4 camera_position_c, glm::vec4 camera_view_vector);
        ~FreeCamera();
        void computePosition();
        void computeView();
        glm::mat4 getViewMatrix();
        float getTheta();
        float getPhi();
        float getDistance();

    private:
};

#endif // FREECAMERA_H
