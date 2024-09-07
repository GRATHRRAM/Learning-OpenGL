#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "shaders.hpp"
#include "renderer.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"

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

    VertexBuffer *vb = new VertexBuffer(vertex, CountOfVertex * sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    
    IndexBuffer *ib = new IndexBuffer(indices, CountOfVertex / 2);

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
            color[0] += rr::Randfloat() * 0.01f;
            color[1] += rr::Randfloat() * 0.01f;
            color[2] += rr::Randfloat() * 0.01f;
        } else {
            color[0] -= rr::Randfloat() * 0.01f;
            color[1] -= rr::Randfloat() * 0.01f;
            color[2] -= rr::Randfloat() * 0.01f;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    delete vb;
    delete ib;

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
