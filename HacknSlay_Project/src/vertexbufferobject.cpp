#include "vertexbufferobject.h"
#include <iostream>

VertexBufferObject::VertexBufferObject(GLfloat* vertices, int size)
{
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{

}
