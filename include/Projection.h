#ifndef PROJECTION_H
#define PROJECTION_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrices.h"
#include "Window.h"

namespace Projection
{
    static float nearplane;
    static float farplane;
    static float field_of_view;
    static glm::mat4 projectionMatrix;


    void init();
    void computeProjectionMatrix();
    glm::mat4 getProjectionMatrix();
    float getNearPlane();
    float getFarPlane();
    float getFieldOfView();
};

#endif // PROJECTION_H
