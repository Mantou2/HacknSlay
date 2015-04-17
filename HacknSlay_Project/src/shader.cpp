#include "shader.h"
#include <fstream>
#include <string>

namespace shader{

    Shader::Shader(const char* filename, GLenum type, const char* name)
        :type(type), name(name)
    {
        loadSource(filename);
        createShader();
    }

    Shader::~Shader()
    {
        glDeleteShader(glShader);
    }

    void Shader::loadSource(const char* filename){
        std::string line;
        std::ifstream file;
        file.open(filename);
        if (file.is_open())
          {
            while ( getline (file,line) )
            {
              codeString += line + "\n";
            }
            file.close();
          }
        code = codeString.c_str();
    }

    void Shader::createShader() {
        glShader = glCreateShader(type);
        glShaderSource(glShader, 1, &code, nullptr);
        glCompileShader(glShader);
        GLint success = 0;
        glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE)
        {
            char buffer[1024];
            glGetShaderInfoLog(glShader, 1024, nullptr, buffer);
            printf("Shader compiler error in %s:\n %s:\n", name, buffer);
        }
    }

}
