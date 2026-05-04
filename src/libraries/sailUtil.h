#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG(x) std::cout << x << std::endl;

namespace sailUtil
{
    std::string repeatString(const std::string& str, int times)
    {
        std::string result;

        for (int i = 0; i < times; i++)
        {
            result += str;
        }

        return result;
    }
    std::string readFile(const std::string& path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}