#include "CharacterController.h"

#define ANIM_SOUTH 3 
#define ANIM_EAST  1 
#define ANIM_WEST  0 
#define ANIM_NORTH 2 

CharacterController::CharacterController(const char* filename, int nAnimations, int nFrames)
    : Sprite(filename, nAnimations, nFrames) {
    this->speed = 0.5f;
    this->velocity = glm::vec2(0.0f);
}

void CharacterController::handleInput(GLFWwindow* window) {
    velocity = glm::vec2(0.0f);
    isMoving = false;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        velocity.y = 1.0f;
        setAnimation(ANIM_NORTH);
        isMoving = true;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        velocity.y = -1.0f;
        setAnimation(ANIM_SOUTH);
        isMoving = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        velocity.x = -1.0f;
        setAnimation(ANIM_WEST);
        isMoving = true;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        velocity.x = 1.0f;
        setAnimation(ANIM_EAST);
        isMoving = true;
    }

    if (glm::length(velocity) > 0.0f) {
        velocity = glm::normalize(velocity);
    }
}

void CharacterController::update(double deltaTime) {
    position += velocity * speed * static_cast<float>(deltaTime);
    
    Sprite::update(deltaTime);
}
