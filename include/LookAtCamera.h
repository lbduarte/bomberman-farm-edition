#ifndef LOOKATCAMERA_H
#define LOOKATCAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "matrices.h"

class LookAtCamera
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
        glm::vec4 m_LookAt_L;
        glm::vec4 m_View_Vector;
        glm::vec4 m_Up_Vector;
        glm::mat4 m_View_Matrix;

    public:
        LookAtCamera(float theta, float phi, float distance, glm::vec4 lookat_point);
        ~LookAtCamera();
        void computePosition();
        void computeView();
        glm::mat4 getViewMatrix();
        float getTheta();
        float getPhi();
        float getDistance();

    private:
};

#endif // LOOKATCAMERA_H
