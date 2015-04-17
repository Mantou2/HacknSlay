#include <GL/glew.h>
#include <glm/glm.hpp>
#include <math.h>
#include <gli/gli.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include <iostream>
#include <string>
#include <SDL.h>

#include "shader.h"
#include "shaderprogram.h"

//------------------------Method Declarations------------------------//
SDL_Window* createWindow();
int getInput(Camera&);
void linkingTransformationMatrix(GLuint, const GLchar *rotation, const GLchar *scalar, const GLchar *view, const GLchar *projection);
void initializeShaderProgram();
void updateScalarMatrix(float scaleFactor);
void updateRotationMatrix(float rotation);
void updateViewMatrix();
void updateProjectionMatrix();

void linkingAttribs(int offset);
void linkingAttribs(GLuint, const GLchar*, int, int, int);

void beginTransformFeedback();
void endTransformFeedback();


void initializeShaderProgramTF();

void fillBufferTF(GLuint, GLuint, int);
void loadTexture();

//-------------------------------------------------------------------//

SDL_Event windowEvent;
SDL_Window* window;

Camera * camera = new Camera(0.1f,glm::vec3(-0.01562f, 1.891585f, -3.51457f), glm::vec3(0.0f,1.5f,0.0f), glm::vec3(0.0f,1.0f,0.0f));

GLuint vbo;
GLuint tbo;
GLuint vao;
GLuint texturB;


GLuint query;
GLuint primitives;

GLfloat vertices[36] = {
     //x ,   y ,  z   ,   r ,  g  ,  b  , normalX, normalY, normalZ, length  texCoord
     0.0f, 0.0f,  0.5f, 1.0f,1.0f,0.0f,   0.0f ,   1.0f ,   0.0f ,   1.0f,  0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.0f,1.0f,0.0f,   0.0f ,   1.0f ,   0.0f ,   1.0f,  1.0f, 1.0f,
     0.5f, 0.0f, -0.5f, 1.0f,0.0f,1.0f,   0.0f ,   1.0f ,   0.0f ,   1.0f,  1.0f, 0.0f,
};

GLint scaleMat;
GLint rotateMat;
GLint viewMat;
GLint projMat;

glm::mat4 scalarMatrix;
glm::mat4 rotationMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

float WINDOW_WIDTH = 800.0f;
float WINDOW_HEIGHT = 600.0f;
float fovy = glm::radians(45.0f);
float aspect = WINDOW_WIDTH/WINDOW_HEIGHT;
float zNear = 0.1f;
float zFar = 30.0f;

float f = 0.0f;
float hacky = 1.0f;
float size = 3.0f;
int tex = 0;
float scaleFactor = 1.0f;

int verticesToDraw = 3;
int index = 3;

int depth = 7;  //Hier verändern für Tiefe des Baumes. Leider nur bis Tiefe 7 möglich.
#include "vertexbufferobject.h"
#include "vertexarrayobject.h"
int main(int argc, char *argv[])
{

    window = createWindow();

    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;

    glewInit();

    shader::Shader vertexShader("HacknSlay_Project/src/shader/vShader.vert", GL_VERTEX_SHADER, "Vertexshader");
    //shader::Shader geometryShader("HacknSlay_Project/src/shader/geomShader.geom", GL_GEOMETRY_SHADER, "Geometryshader");
    shader::Shader fragmentShader("HacknSlay_Project/src/shader/fragShader.frag", GL_FRAGMENT_SHADER, "Fragmentshader");

    shader::Shaderprogram program(vertexShader, fragmentShader, "outColor", false);

    VertexBufferObject vertexBuffObj(&vertices[0], 36);

    VertexArrayObject vertexArrObj;

    linkingTransformationMatrix(program.getGLProgram(), "rotateMat", "scaleMat", "viewMat", "projMat");
    linkingAttribs(program.getGLProgram(), "vPosition", 3, 12, 0);
    linkingAttribs(program.getGLProgram(), "vColor"   , 3, 12, 3);
    linkingAttribs(program.getGLProgram(), "vNormal"  , 3, 12, 6);
    linkingAttribs(program.getGLProgram(), "vTexCoord", 2, 12, 10);

    int tex = 0;

    GLint uTex = glGetUniformLocation(program.getGLProgram(), "texWood");
    glUniform1i(uTex, tex);

    glGenTextures(1, &texturB);
    loadTexture();
    glEnable(GL_DEPTH_TEST);

    while (true)
    {
        if(getInput(*camera) == -1){
            break;
        }else if(getInput(*camera) == 0){
            updateViewMatrix();
        }else if(getInput(*camera) == 2){
            //initializeShaderProgramTF();


        }
        // Clear the screen to black
        glClearColor(0.0,0.0,0.0,1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Swap buffers
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
}

SDL_Window* createWindow(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window* window = SDL_CreateWindow("Real-Time Rendering", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    return window;
}

int getInput(Camera &camera){

    if (SDL_PollEvent(&windowEvent))
    {
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);

        switch(windowEvent.type){
            case SDL_KEYUP:
                if(keyState[SDL_SCANCODE_ESCAPE]){
                    return -1;
                }
            break;

            case SDL_KEYDOWN:
                if(keyState[SDL_SCANCODE_ESCAPE]){
                    return -1;
                }else
                if(keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A]){
                    camera.move(FORWARD_LEFT);
                }else if(keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D]){
                    camera.move(FORWARD_RIGHT);
                }else if(keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_A]){
                    camera.move(BACKWARD_LEFT);
                }else if(keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_D]){
                    camera.move(BACKWARD_RIGHT);
                }else if(keyState[SDL_SCANCODE_I]&& keyState[SDL_SCANCODE_A]){
                    camera.move(TOP_LEFT);
                }else if(keyState[SDL_SCANCODE_I] && keyState[SDL_SCANCODE_D]){
                    camera.move(TOP_RIGHT);
                }else if(keyState[SDL_SCANCODE_K] && keyState[SDL_SCANCODE_A]){
                    camera.move(DOWN_LEFT);
                }else if(keyState[SDL_SCANCODE_K] && keyState[SDL_SCANCODE_D]){
                    camera.move(DOWN_RIGHT);
                }else if(keyState[SDL_SCANCODE_W]){
                    camera.move(FORWARD);
                }else if(keyState[SDL_SCANCODE_A]){
                    camera.move(LEFT);
                }else if(keyState[SDL_SCANCODE_S]){
                    camera.move(BACKWARD);
                }else if(keyState[SDL_SCANCODE_D]){
                    camera.move(RIGHT);
                }else if(keyState[SDL_SCANCODE_I]){
                    camera.move(TOP);
                }else if(keyState[SDL_SCANCODE_K]){
                    camera.move(DOWN);
                }
            break;

            default:
                break;
        }
        return 0;
    }
    return 1;
}

void linkingTransformationMatrix(GLuint program, const GLchar *rotation, const GLchar *scalar, const GLchar *view, const GLchar *projection){
    scalarMatrix = glm::scale(scalarMatrix, glm::vec3(1.0f,1.0f,1.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    if(!camera){
    viewMatrix = glm::lookAt(
                camera->getPosition(),
                camera->getLookAtVector(),
                camera->getUpVector()
              );
    }
    projectionMatrix = glm::perspective(fovy,aspect,zNear,zFar);
    projMat = glGetUniformLocation(program, projection);
    glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    viewMat = glGetUniformLocation(program, view);
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    rotateMat = glGetUniformLocation(program, rotation);
    glUniformMatrix4fv(rotateMat, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

    scaleMat = glGetUniformLocation(program, scalar);
    glUniformMatrix4fv(scaleMat, 1, GL_FALSE, glm::value_ptr(scalarMatrix));
}

void updateScalarMatrix(float scaleFactor){
    scalarMatrix = glm::scale(scalarMatrix, glm::vec3(scaleFactor,scaleFactor, scaleFactor));
    glUniformMatrix4fv(scaleMat, 1, GL_FALSE, glm::value_ptr(scalarMatrix));
}

void updateRotationMatrix(float rotation){
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(rotateMat, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}

void updateViewMatrix(){

        viewMatrix = glm::lookAt(
                    camera->getPosition(),
                    camera->getLookAtVector(),
                    camera->getUpVector()
                  );
        glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}

void updateProjectionMatrix(){
    projectionMatrix = glm::perspective(fovy,aspect,zNear,zFar);
    glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void linkingAttribs(GLuint program, const GLchar *attribName, int size, int stride, int offset){
    GLint attrib = glGetAttribLocation(program, attribName);
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (void*)(sizeof(GLfloat)*offset));
}

void loadTexture(){
   gli::texture2D texture(gli::load_dds("C:/Users/Gimmillaro Fabio/Desktop/Projekte/Real Time Rendering Hausarbeit/RTR-Project/build/textures/TreeTextur2.dds"));
   assert(!texture.empty());
   glBindTexture(GL_TEXTURE_2D, texturB);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(texture.levels() - 1));
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
   glTexStorage2D(GL_TEXTURE_2D,
   GLint(texture.levels()),
   GLenum(gli::internal_format(texture.format())),
   GLsizei(texture.dimensions().x),
   GLsizei(texture.dimensions().y));
   if(gli::is_compressed(texture.format()))
   {
       for(gli::texture2D::size_type level = 0; level < texture.levels(); ++level)
       {
           glCompressedTexSubImage2D(GL_TEXTURE_2D,
           GLint(level),
           0, 0,
           GLsizei(texture[level].dimensions().x),
           GLsizei(texture[level].dimensions().y),
           GLenum(gli::internal_format(texture.format())),
           GLsizei(texture[level].size()),
           texture[level].data());
       }
   }
   else
   {
       for(gli::texture2D::size_type level = 0; level < texture.levels(); ++level)
       {
           glTexSubImage2D(GL_TEXTURE_2D,
           GLint(level),
           0, 0,
           GLsizei(texture[level].dimensions().x),
           GLsizei(texture[level].dimensions().y),
           GLenum(gli::external_format(texture.format())),
           GLenum(gli::type_format(texture.format())),
           texture[level].data());
       }
   }
   glActiveTexture(GL_TEXTURE1);
}
