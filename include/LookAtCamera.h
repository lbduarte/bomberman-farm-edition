#ifndef LOOKATCAMERA_H
#define LOOKATCAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrices.h"

namespace Cameras
{
    namespace LookAt
    {

            static float theta;
            static float phi;
            static float distance;
            static float r;
            static float y;
            static float z;
            static float x;
            static glm::vec4 position_C;
            static glm::vec4 lookAt_L;
            static glm::vec4 viewVector;
            static glm::vec4 upVector;
            static glm::mat4 viewMatrix;


            void init(float a_theta, float a_phi, float a_distance, glm::vec4 lookat_point);
            void computePosition();
            void computeViewMatrix();

            glm::mat4 getViewMatrix();
            float getTheta();
            float getPhi();
            float getDistance();
            void updateTheta(float dx);
            void updatePhi(float dy);
            void updateDistance(double yoffset);

    }
}

#endif // LOOKATCAMERA_H
