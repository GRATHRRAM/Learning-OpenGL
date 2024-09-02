#pragma once
#include <string>

namespace shaders {
	std::string LoadShader(const std::string path);
	unsigned int CompileShader(unsigned int type, const std::string* source);
	unsigned int CreateShader(const std::string* VertexShader, const std::string* FragmentShader);
}
