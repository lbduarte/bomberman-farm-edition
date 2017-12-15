#ifndef FREECAMERA_H
#define FREECAMERA_H

#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrices.h"
#include "Keyboard.h"
#include "VirtualScene.h"

namespace Cameras
{
    namespace Free
    {
            static float theta;
            static float phi;
            static float distance;
            static float r;
            static float y;
            static float z;
            static float x;
            static glm::vec4 position_C;
            static glm::vec4 incVector;
            static glm::vec4 viewVector;
            static glm::vec4 upVector;
            static glm::mat4 viewMatrix;

            static glm::vec4 movementVector;
            static glm::vec4 bottomNearLeft;
            static glm::vec4 topFarRight;


            void init(float a_theta, float a_phi, float a_distance, glm::vec4 camera_position_c, glm::vec4 camera_view_vector);
            void updateCamera();
            void computeViewMatrix();

            glm::mat4 getViewMatrix();
            float getTheta();
            float getPhi();
            float getDistance();
            void updateTheta(float dx);
            void updatePhi(float dy);
            void updateDistance(double yoffset);
            glm::vec4 getPosition();
            glm::vec4 getIncVector();
            glm::vec4 getUpVector();
            void updatePosition(glm::vec4 position);
    }
}
#endif // FREECAMERA_H
