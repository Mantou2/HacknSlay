#include "camera.h"

//Diese Klasse entsprechend umschreiben
//Was getan werden muss:
//1. Camera braucht eine Viewmatrix. Als Argument soll noch ein const GLchar* mitgegeben werden, wie diese Viewmatrix im Shader heisst.
//2. Evtl. braucht sie noch die Anzahl der Shader und für jeden Shader einen "eigenen" Namen für die Viewmatrix (Wird am besten in einem vector<const GLchar*> gespeichert bzw. noch ein vector<Shader> oder so
//3. Es gibt eine Methode updateViewMatrix(Shader). Damit in diesem Shader die Viewmatrix geändert werden kann.
//4. Am besten geben wir einem Shader noch ein Attribut, in dem alle Variablen, die im shader vorkommen gespeichert sind. (Bsp: vector<const GLchar*> {"position","normal","color",...} usw.)
//5.

Camera::Camera(float velocity, vec3 camPos, vec3 lookAt, vec3 upVec)
    :cameraPosition(camPos), lookAtVector(lookAt), upVector(upVec)
{
    this->velocity = velocity;
    computeDirectionAndRightVector();
}

Camera::~Camera()
{

}

void Camera::setPosition(vec3 newPosition){
    this->cameraPosition = newPosition;
    computeDirectionAndRightVector();
}

vec3 Camera::getPosition(){
    return cameraPosition;
}

void Camera::setUpVector(vec3 newPosition){
    this->cameraPosition = newPosition;
    computeDirectionAndRightVector();
}

vec3 Camera::getUpVector(){
    return upVector;
}

void Camera::setLookAtVector(vec3 newPosition){
    this->cameraPosition = newPosition;
    computeDirectionAndRightVector();
}

vec3 Camera::getLookAtVector(){
    return lookAtVector;
}

vec3 Camera::getDirectionVector(){
    return directionVector;
}

vec3 Camera::getRightVector(){
    return rightVector;
}

void Camera::computeDirectionAndRightVector(){
    directionVector = normalize(lookAtVector - cameraPosition);
    rightVector = normalize(cross(directionVector, upVector));
}

float Camera::getVelocity(){
    return velocity;
}

void Camera::setVelocity(float velocity){
    this->velocity = velocity;
}
#include <iostream>
void Camera::move(Direction dir){
    switch(dir){
    case TOP_RIGHT:
        cameraPosition += upVector * velocity;
        cameraPosition += rightVector * velocity;
        break;
    case TOP_LEFT:
        cameraPosition += upVector * velocity;
        cameraPosition -= rightVector * velocity;
        break;
    case DOWN_RIGHT:
        cameraPosition -= upVector * velocity;
        cameraPosition += rightVector * velocity;
        break;
    case DOWN_LEFT:
        cameraPosition -= upVector * velocity;
        cameraPosition -= rightVector * velocity;
        break;
    case FORWARD_RIGHT:
        cameraPosition += directionVector * velocity;
        cameraPosition += rightVector * velocity;
        break;
    case FORWARD_LEFT:
        cameraPosition += directionVector * velocity;
        cameraPosition -= rightVector * velocity;
        break;
    case BACKWARD_RIGHT:
        cameraPosition -= directionVector * velocity;
        cameraPosition += rightVector * velocity;
        break;
    case BACKWARD_LEFT:
        cameraPosition -= directionVector * velocity;
        cameraPosition -= rightVector * velocity;
        break;
    case TOP:
        std::cout << upVector.x << upVector.y << std::endl;
        cameraPosition += upVector * velocity;
        break;
    case DOWN:
        cameraPosition -= upVector * velocity;
        break;
    case FORWARD:
        cameraPosition += directionVector * velocity;
        break;
    case BACKWARD:
        cameraPosition -= directionVector * velocity;
        break;
    case RIGHT:
        cameraPosition += rightVector * velocity;
        break;
    case LEFT:
        cameraPosition -= rightVector * velocity;
        break;
    default:
        break;

    }
    computeDirectionAndRightVector();
}

