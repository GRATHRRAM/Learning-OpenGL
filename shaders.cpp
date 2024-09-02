#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include "shaders.hpp"

unsigned int shaders::CompileShader(unsigned int type, const std::string* source) {
    unsigned int id = glCreateShader(type);
    const char* src = source->c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int resoult = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &resoult);
    if (resoult == GL_FALSE) {
        int len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*) alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        if (type == GL_VERTEX_SHADER) std::cout << "OpenGl Vertex shader Compilation faild\n" << message << "\n";
        else std::cout << "OpenGl Fragment shader Compilation faild\n" << message << "\n";
        return 0;
    }

    return id;
}

unsigned int shaders::CreateShader(const std::string* VertexShader, const std::string* FragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = shaders::CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = shaders::CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

std::string shaders::LoadShader(const std::string path) {
    std::string buff = "";

    std::fstream file(path, std::ios::in);

    if (!file.is_open()) {
        std::cout << "Failed to Load Shader: " << path << "\n";
        return "err";
    }

    std::string line;
    while (std::getline(file, line)) {
        buff += line + '\n';
    }

    file.close();
    return buff;
}
