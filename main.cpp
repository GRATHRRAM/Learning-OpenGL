#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.hpp"

int main(void) {
    GLFWwindow* window;

    if(!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "SpaceWar", NULL, NULL);
    
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) return -2;

    std::cout << "OpenGL -> Version: " << glGetString(GL_VERSION) << "\n\n";

    float vertex[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buff = 0;
    glGenBuffers(1, &buff);
    glBindBuffer(GL_ARRAY_BUFFER, buff); 
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertex, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    std::string vertexshader = shaders::LoadShader("./shaders/vertex.glsl");
    std::string fragmentshader = shaders::LoadShader("./shaders/fragment.glsl");

    if(vertexshader == "err" || fragmentshader == "err") return -3;

    unsigned int shader = shaders::CreateShader(&vertexshader, &fragmentshader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
