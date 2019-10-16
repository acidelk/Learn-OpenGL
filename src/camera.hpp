#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.hpp"
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    GLfloat pinch;
    GLfloat yaw;
    GLfloat mouseSensitive;
    GLfloat movementSpeed;

    Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            GLfloat yaw = -90.0f,
            GLfloat pinch = 0.0f,
            GLfloat mouseSensitive = 0.05f,
            GLfloat movementSpeed = 3.0f
    ) {
        this->position = position;
        this->front = front;
        this->up = up;
        this->yaw = yaw;
        this->pinch = pinch;
        this->mouseSensitive = mouseSensitive;
        this->movementSpeed = movementSpeed;
    }

    void ProcessMouse(GLfloat xpos, GLfloat ypos);

    void Move(GLfloat deltaTime);

    void ProcessKey(GLint key, GLboolean value);

    void SetMouseStartPosition(GLfloat x, GLfloat y);

    glm::mat4 View();

private:
    GLboolean keys[1024];
    GLfloat lastMouseX;
    GLfloat lastMouseY;
};


#endif //CAMERA_H
