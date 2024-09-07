#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "shaders.hpp"

namespace rr {
    float Randfloat();
    void ClearErrors();
    void PrintErrors();
}
