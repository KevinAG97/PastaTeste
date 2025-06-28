#pragma once
#include "Sprite.h"
#include <GLFW/glfw3.h> 

class CharacterController : public Sprite
{
public:
    CharacterController(const char* filename, int nAnimations, int nFrames);
    
    // Novas funções
    void handleInput(GLFWwindow* window);
    virtual void update(double deltaTime) override;

private:
    float speed;
    glm::vec2 velocity;
};
