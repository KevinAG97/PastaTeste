#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Sprite {
public:
    Sprite();
    Sprite(const char* textureFile, int nAnimations, int nFrames);
    virtual ~Sprite();

    void setup(const char* textureFile, int nAnimations, int nFrames);
    virtual void update(double deltaTime);
    void draw();
    
    // Define qual linha da animação usar
    void setAnimation(int animIndex);

protected: 
    GLuint shader_programme;
    GLuint VAO, VBO, EBO;
    GLuint texture;
    
    glm::vec2 position; 

    int nAnimations;
    int nFrames;
    int currentFrame;
    int currentAnimation;

    bool isMoving;

    float animation_speed;
    double last_frame_time;

    float frame_width;
    float frame_height;
};

#endif
