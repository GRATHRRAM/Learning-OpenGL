#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "shaders.hpp"

inline float randfloat() {
    return (rand() % 65535) / 65535.f;
}

void glClearErrors() {
    while(glGetError() != GL_NO_ERROR);
}

void glPrintErrors() {
    while(GLenum error = glGetError()) {
        std::cout << "OpenGL -> Error -> { " << error << "}\n";
    }
}

int main(void) {
    srand(time(0));
    GLFWwindow* window;

    if(!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "SpaceWar", NULL, NULL);
    
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) return -2;

    std::cout << "OpenGL -> Version: " << glGetString(GL_VERSION) << "\n\n";
    
    const int CountOfVertex = 12;
    float vertex[CountOfVertex] = {
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        
        0.5f, -0.5f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    unsigned int buff = 0;
    glGenBuffers(1, &buff);
    glBindBuffer(GL_ARRAY_BUFFER, buff); 
    glBufferData(GL_ARRAY_BUFFER, CountOfVertex * sizeof(float), vertex, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    
    unsigned int ibo = 0;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, CountOfVertex * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    std::string vertexshader = shaders::LoadShader("./shaders/vertex.glsl");
    std::string fragmentshader = shaders::LoadShader("./shaders/fragment.glsl");

    if(vertexshader == "err" || fragmentshader == "err") return -3;

    unsigned int shader = shaders::CreateShader(&vertexshader, &fragmentshader);
    glUseProgram(shader);
    
    int loc = glGetUniformLocation(shader, "u_Color");
    if(loc == -1) std::cout << "OpenGL -> Shader -> u_Color is unused\n"; 
    
    float color[] = {
        0.f,
        0.f,
        0.f,
    };

    bool inc = true;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(loc,color[0],color[1],color[2],1.0f);
        glDrawElements(GL_TRIANGLES, CountOfVertex / 2, GL_UNSIGNED_INT, nullptr);
        
        if(color[0] > 1.f) inc = false;
        if(color[1] > 1.f) inc = false;
        if(color[2] > 1.f) inc = false;

        if(color[0] < 0.f) inc = true;
        if(color[1] < 0.f) inc = true;
        if(color[2] < 0.f) inc = true;

        if(inc) {
            color[0] += randfloat() * 0.01f;
            color[1] += randfloat() * 0.01f;
            color[2] += randfloat() * 0.01f;
        } else {
            color[0] -= randfloat() * 0.01f;
            color[1] -= randfloat() * 0.01f;
            color[2] -= randfloat() * 0.01f;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
