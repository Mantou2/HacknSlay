#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

using namespace glm;


    enum Direction{
        TOP,
        DOWN,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        TOP_RIGHT,
        TOP_LEFT,
        DOWN_RIGHT,
        DOWN_LEFT,
        FORWARD_RIGHT,
        FORWARD_LEFT,
        BACKWARD_RIGHT,
        BACKWARD_LEFT,
    };

    class Camera
    {
    public:

        Camera(float, vec3, vec3, vec3);
        ~Camera();

        void setPosition(vec3);
        vec3 getPosition();

        void setUpVector(vec3);
        vec3 getUpVector();

        void setLookAtVector(vec3);
        vec3 getLookAtVector();

        vec3 getDirectionVector();
        vec3 getRightVector();

        void setVelocity(float);
        float getVelocity();

        void computeDirectionAndRightVector();

        void move(Direction direction);

        void lookTo();

    private:
        vec3 cameraPosition;
        vec3 upVector;
        vec3 lookAtVector;
        vec3 directionVector;
        vec3 rightVector;

        float velocity;

        float fovy;
        float aspect;
        float zNear;
        float zFar;

    };


#endif // CAMERA_H
