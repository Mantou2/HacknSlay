#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <gl/glew.h>

class VertexBufferObject
{
public:
    VertexBufferObject(GLfloat*, int);
    ~VertexBufferObject();
private:
    GLuint vbo;
};

#endif // VERTEXBUFFEROBJECT_H
