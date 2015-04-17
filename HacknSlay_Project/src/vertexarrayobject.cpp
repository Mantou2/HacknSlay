#include "vertexarrayobject.h"
#include <iostream>
VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

VertexArrayObject::~VertexArrayObject()
{

}

