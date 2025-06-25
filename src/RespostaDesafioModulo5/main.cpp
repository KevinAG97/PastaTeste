#include "gl_utils.h"
#include "CharacterController.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int g_gl_width = 800;
int g_gl_height = 600;
GLFWwindow *g_window = NULL;

int main() {
    start_gl();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    stbi_set_flip_vertically_on_load(true);

    CharacterController player("Vampires3.png", 4, 6);
    
    double last_time = glfwGetTime();

    while (!glfwWindowShouldClose(g_window)) {
        double current_time = glfwGetTime();
        double delta_time = current_time - last_time;
        last_time = current_time;

        _update_fps_counter(g_window);
        
        if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(g_window, 1);
        }

        player.handleInput(g_window);
        
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, g_gl_width, g_gl_height);

        player.update(delta_time); 
        player.draw();

        glfwPollEvents();
        glfwSwapBuffers(g_window);
    }

    glfwTerminate();
    return 0;
}
