#pragma once

#include <vector>
#include <glad/glad.h>

class Mesh
{
    /*
    Vertices in general (for note)
    vertexPosition(3),vertexNormal(3),textureCoordinates(2)
    */

    public:
        unsigned int VBO,VAO;

        std::vector<float> vertices;
        unsigned int vertexCount;
        Mesh(std::vector<float>& vertices): vertices(vertices){

            vertexCount = vertices.size()/8;

            glGenVertexArrays(1,&VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1,&VBO);
            glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),vertices.data(),GL_STATIC_DRAW);


            //Vertex Position
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(0));
            glEnableVertexAttribArray(0);

            //Vertex Normal
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);

            //UV
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindVertexArray(0);
        };
        void bind()
        {
            glBindVertexArray(VAO);
        }
        
    private:
};