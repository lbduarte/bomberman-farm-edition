#ifndef PLAYER_H
#define PLAYER_H

#include <glm/vec4.hpp>
#include "FreeCamera.h"
#include "VirtualScene.h"

namespace Player
{
    static glm::vec4 position;
    static glm::vec4 movementVector;

    // Bounding Box
    static glm::vec4 bottomNearLeft;
    static glm::vec4 topFarRight;




    void init();
    void updatePosition();
    void input();
    glm::vec4 getTopFarRight();
    glm::vec4 getBottomNearLeft();
    glm::vec4 getPosition();

}

#endif // PLAYER_H
