#ifndef FREECAMERA_H
#define FREECAMERA_H

#include <glad/glad.h>   // OpenGL 3.3 Context Creation
#include <GLFW/glfw3.h>  // Windowing Library
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrices.h"
#include "Keyboard.h"

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


            void init(float a_theta, float a_phi, float a_distance, glm::vec4 camera_position_c, glm::vec4 camera_view_vector);
            void computePosition();
            void computeViewMatrix();
    }
}
#endif // FREECAMERA_H
