#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <gl/glew.h>

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
private:
    GLuint vao;
};

#endif // VERTEXARRAYOBJECT_H
