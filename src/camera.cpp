#include "camera.hpp"

void Camera::ProcessMouse(GLfloat xpos, GLfloat ypos) {
    GLfloat xoffset = xpos - this->lastMouseX;
    GLfloat yoffset = this->lastMouseY - ypos;
    this->lastMouseX = xpos;
    this->lastMouseY = ypos;

    xoffset *= this->mouseSensitive;
    yoffset *= this->mouseSensitive;

    this->yaw += xoffset;
    this->pinch += yoffset;

    if (this->pinch <= -89.0f) {
        this->pinch = -89.0f;
    }
    if (this->pinch >= 89.0f) {
        this->pinch = 89.0f;
    }

    this->front = glm::normalize(
            glm::vec3(
                    cos(glm::radians(this->yaw)) * cos(glm::radians(this->pinch)),
                    sin(glm::radians(this->pinch)),
                    sin(glm::radians(this->yaw)) * cos(glm::radians(this->pinch))
            )
    );
}

void Camera::Move(GLfloat deltaTime) {
    GLfloat camera_speed = this->movementSpeed * deltaTime;
    if (this->keys[GLFW_KEY_W]) {
        this->position += camera_speed * this->front;
    }
    if (this->keys[GLFW_KEY_S]) {
        this->position -= camera_speed * this->front;
    }
    if (this->keys[GLFW_KEY_A]) {
        this->position += glm::normalize(glm::cross(this->up, this->front)) * camera_speed;
    }
    if (this->keys[GLFW_KEY_D]) {
        this->position += glm::normalize(glm::cross(this->front, this->up)) * camera_speed;
    }
}

glm::mat4 Camera::View() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKey(GLint key, GLboolean value) {
    this->keys[key] = value;
}

void Camera::SetMouseStartPosition(GLfloat x, GLfloat y) {
    this->lastMouseX = x;
    this->lastMouseY = y;
}

