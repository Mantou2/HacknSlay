#ifndef SHADER_H
#define SHADER_H

#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

namespace shader{
    class Shader
    {
    public:
        Shader(const char*, GLenum, const char*);
        ~Shader();
        void loadSource(const char*);
        const GLchar* getCode()const{return code;}
        GLuint getGLShader()const{return glShader;}
        void createShader();
        GLenum getShaderType()const{return type;}
        void fillAttributeVector();
    private:
        const GLchar* code;
        GLenum type;
        GLuint glShader;
        const char* name;
        std::string codeString;
        std::vector<const GLchar*> attributes;
    };
}

#endif // SHADER_H
