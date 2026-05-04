#pragma once

#include <string>

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
}