#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <gl/glew.h>
#include "shader.h"

namespace shader{

    class Shaderprogram
    {
    public:
        Shaderprogram(Shader, Shader, Shader, const GLchar*, bool);
        Shaderprogram(Shader, Shader, const GLchar*, bool);
        Shaderprogram(Shader, const GLchar*, bool);
        ~Shaderprogram();
        void useProgram();
        void linkAttribute(const GLchar*, int, int, int);
        GLuint getGLProgram()const{return program;}

    private:
        GLuint program;
        bool hasVertexshader = false;
        bool hasGeometryshader = false;
        bool hasFragmentshader = false;
    };

}

#endif // SHADERPROGRAM_H
