#include "Player.h"

void Player::init()
{
    position = Cameras::Free::getPosition();
    bottomNearLeft = glm::vec4(position.x - 0.25, position.y - 0.25, position.z + 0.25, 1.0f);
    topFarRight = glm::vec4(position.x + 0.25, position.y + 0.25, position.z - 0.25, 1.0f);
}

void Player::updatePosition()
{


    movementVector.y = 0;

    if(length(movementVector) > 0)
        movementVector = normalize(movementVector);

    glm::vec4 oldPosition = Cameras::Free::getPosition();
    glm::vec4 newPosition = oldPosition + movementVector * 0.03f;

    glm::vec4 collisionVector = Graphics::VirtualScene::checkCollision(oldPosition, newPosition, bottomNearLeft, topFarRight);
    //movementVector = movementVector * collisionVector;

    position = oldPosition + movementVector;

    bottomNearLeft = glm::vec4(position.x - 0.25, position.y - 0.25, position.z + 0.25, 1.0f);
    topFarRight = glm::vec4(position.x + 0.25, position.y + 0.25, position.z - 0.25, 1.0f);

    Cameras::Free::updatePosition(position);
}

void Player::input()
{
    movementVector = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_D))
        movementVector -= crossproduct(Cameras::Free::getUpVector(), Cameras::Free::getIncVector());

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_A))
        movementVector += crossproduct(Cameras::Free::getUpVector(), Cameras::Free::getIncVector());

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_W))
        movementVector += Cameras::Free::getIncVector();

    if (Input::Keyboard::isKeyPressed(GLFW_KEY_S))
        movementVector -= Cameras::Free::getIncVector();


}

glm::vec4 Player::getBottomNearLeft()
{
    return bottomNearLeft;
}

glm::vec4 Player::getTopFarRight()
{
    return topFarRight;
}

glm::vec4 Player::getPosition()
{
    return position;
}
