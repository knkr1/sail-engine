#pragma once

#include <vector>
#include <glad/glad.h>

class Mesh {
    public:
        unsigned int indexCount;
        Mesh(std::vector<float> vertices,int ic=36)
        {
            glGenVertexArrays(1,&VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1,&VBO);
            glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),vertices.data(),GL_STATIC_DRAW);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindVertexArray(0);

            indexCount = ic;
        }
        void bind()
        {
            glBindVertexArray(VAO);
        }
    private:
        unsigned int VAO,VBO;
};