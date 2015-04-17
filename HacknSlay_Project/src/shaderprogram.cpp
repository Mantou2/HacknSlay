#include "shaderprogram.h"
#include <iostream>
namespace shader{

//Es müssen noch Errors im Konstruktor von Shader geschmissen werden, falls type != Vertex-Frag -oder Geometryshader
    Shaderprogram::Shaderprogram(Shader v, Shader g, Shader f, const GLchar* dataLocation, bool tf)
    {
        if((v.getShaderType() != g.getShaderType()) && (v.getShaderType() != f.getShaderType()) && (g.getShaderType() != f.getShaderType())){
            program = glCreateProgram();
            hasVertexshader = true;
            hasGeometryshader = true;
            hasFragmentshader = true;
            glAttachShader(program, v.getGLShader());
            glAttachShader(program, g.getGLShader());
            glAttachShader(program, f.getGLShader());
            if(tf){
                const GLchar* feedbackVaryings[] = {"fPosition","fColor","fNormal","fLength","fTexCoord"};
                glTransformFeedbackVaryings(program, 5, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
            }
            glBindFragDataLocation(program, 0, dataLocation);
            glLinkProgram(program);
            glUseProgram(program);
        }else{
            std::cout << "Dieses Program enthält ungünstige Werte. Bitte neue Shader linken." << std::endl;
        }
    }

    Shaderprogram::Shaderprogram(Shader v, Shader gOrf, const GLchar* dataLocation, bool tf)
    {
        if(v.getShaderType() != gOrf.getShaderType() && (v.getShaderType() == GL_VERTEX_SHADER || gOrf.getShaderType() == GL_VERTEX_SHADER)){
            std::cout << "Program erfolgreich gelinkt" << std::endl;
            program = glCreateProgram();
            glAttachShader(program, v.getGLShader());
            glAttachShader(program, gOrf.getGLShader());
            if(tf){
                const GLchar* feedbackVaryings[] = {"fPosition","fColor","fNormal","fLength","fTexCoord"};
                glTransformFeedbackVaryings(program, 5, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
            }
            glBindFragDataLocation(program, 0, dataLocation);
            glLinkProgram(program);
            glUseProgram(program);
            hasVertexshader = true;
            //-------------------------oder hasGeometryShader------------------------//
            hasFragmentshader = true;
        }else{
            std::cout << "Dieses Program enthält ungünstige Werte. Bitte neue Shader linken. " << std::endl;
        }
    }

    Shaderprogram::Shaderprogram(Shader v, const GLchar* dataLocation, bool tf){
        if(v.getShaderType() == GL_VERTEX_SHADER){
            program = glCreateProgram();
            hasVertexshader = true;
            glAttachShader(program, v.getGLShader());
            if(tf){
                const GLchar* feedbackVaryings[] = {"fPosition","fColor","fNormal","fLength","fTexCoord"};
                glTransformFeedbackVaryings(program, 5, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
            }
            glBindFragDataLocation(program, 0, dataLocation);
            glLinkProgram(program);
            glUseProgram(program);
        }else{
            std::cout << "Dieses Program enthält ungünstige Werte. Bitte neue Shader linken." << std::endl;
        }
    }

    Shaderprogram::~Shaderprogram()
    {
        glDeleteProgram(program);
    }

    void Shaderprogram::useProgram(){
        glUseProgram(program);
    }

    void Shaderprogram::linkAttribute(const GLchar *attribName, int size, int stride, int offset){
        GLint attrib = glGetAttribLocation(program, attribName);
        glEnableVertexAttribArray(attrib);
        glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (void*)(sizeof(GLfloat)*offset));
    }
}

