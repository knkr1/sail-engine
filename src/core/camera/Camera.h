#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/window/Window.h"
#include "core/event/Event.h"

class Render;

class Camera
{
    public:

        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);


        float sensitivity = 0.1f;
        float lastX = 400;
        float lastY = 300;

        float yaw = -90.0f;
        float pitch = 0;
        float cameraSpeed = 1;

        float fov = 45.0f;



        bool firstCapture = true;
        bool isCaptured = true;

        Camera() {
        }   

        glm::mat4 getViewMatrix()
        {
            return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        }

        glm::mat4 getProjectionMatrix(Window& window)
        {
            return glm::perspective(glm::radians(fov),(float)window.width/(float)window.height,0.1f,100.0f);
        }


        void processKeyboard(GLFWwindow* window, float deltaTime)
        {   
            float calculatedSpeed = cameraSpeed * deltaTime * 2.5;
            if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
                cameraPos += calculatedSpeed * cameraFront;
            if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
                cameraPos -= calculatedSpeed * glm::normalize(glm::cross(cameraFront,cameraUp));
            if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
                cameraPos -= calculatedSpeed * cameraFront;
            if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
                cameraPos += calculatedSpeed * glm::normalize(glm::cross(cameraFront,cameraUp));
        }

        void processMouse(GLFWwindow* window, double xpos, double ypos)
        {
            if(isCaptured || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
            {
                if(firstCapture)
                {
                    firstCapture = false;
                    lastX = xpos;  // use actual position, not window center
                    lastY = ypos;
                    return;  // skip this frame entirely
                }
                float xoffset = xpos - lastX;
                float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

                xoffset *= sensitivity;
                yoffset *= sensitivity;

                yaw   += xoffset;
                pitch += yoffset;   

                if(pitch > 89.0f)
                    pitch =  89.0f;
                if(pitch < -89.0f)
                    pitch = -89.0f;
                glm::vec3 direction;
                direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                direction.y = sin(glm::radians(pitch));
                direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                cameraFront = glm::normalize(direction);
            }
            lastX = xpos;
            lastY = ypos;
        }
    private:

};