#include "renderer.hpp"

float rr::Randfloat() {
    return (rand() % 65535) / 65535.f;
}

void rr::ClearErrors() {
    while(glGetError() != GL_NO_ERROR);
}

void rr::PrintErrors() {
    while(GLenum error = glGetError()) {
        std::cout << "OpenGL -> Error -> { " << error << "}\n";
    }
}
