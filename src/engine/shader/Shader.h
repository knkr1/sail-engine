#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>

#include "libraries/sailUtil.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    public:

        unsigned int shaderID;

        Shader(std::string vertexPath, std::string fragmentPath)
        {
            std::string vertexString = sailUtil::readFile(vertexPath);
            std::string fragmentString = sailUtil::readFile(fragmentPath);
            const char* vertexSource = vertexString.c_str();
            const char* fragmentSource = fragmentString.c_str();

            unsigned int vertexID, fragmentID;
            
            //Vertex
            vertexID = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexID,1,&vertexSource,NULL);
            glCompileShader(vertexID);
            checkErrors(vertexID,"VERTEX");

            //Fragment
            fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentID,1,&fragmentSource,NULL);
            glCompileShader(fragmentID);
            checkErrors(fragmentID,"FRAGMENT");

            //Program

            shaderID = glCreateProgram();
            glAttachShader(shaderID,vertexID);
            glAttachShader(shaderID,fragmentID);
            glLinkProgram(shaderID);

            checkCompileErrors(shaderID);

            glDeleteShader(vertexID);
            glDeleteShader(fragmentID);  
        }

        void bind()
        {
            glUseProgram(shaderID);
        }

        void setBool(const std::string &name, bool value) const
        {         
            glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value); 
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value); 
        }
        // ------------------------------------------------------------------------


        void setFloat(const std::string& name, float value) const {
            glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
        }

        void setFloat(const std::string& name, glm::vec2 value) const {
            glUniform2f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y);
        }

        void setFloat(const std::string& name, glm::vec3 value) const {
            glUniform3f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z);
        }

        void setFloat(const std::string& name, glm::vec4 value) const {
            glUniform4f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z, value.w);
        }


        void setMat4(std::string uniformName, glm::mat4 data) const
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(data));
        }

    private:
        void checkErrors(unsigned int shaderID, std::string identifier = "UNKNOWN_TYPE")
        {
            int success;
            char infoString[512];
            glGetShaderiv(shaderID,GL_COMPILE_STATUS,&success);
            if(!success)
            {
                glGetShaderInfoLog(shaderID, 512, NULL, infoString);
                std::cout << "ERROR::SHADER::"<< identifier <<"::COMPILATION_FAILED\n" << infoString << std::endl;
            }
        }
        void checkCompileErrors(unsigned int shaderID)
        {
            int success;
            char infoString[512];
            glGetProgramiv(shaderID,GL_LINK_STATUS,&success);
            if(!success)
            {
                glGetProgramInfoLog(shaderID, 512, NULL, infoString);
                std::cout << "ERROR::SHADER::"<< "COMPILING" <<"::COMPILATION_FAILED\n" << infoString << std::endl;
            }
        }
};