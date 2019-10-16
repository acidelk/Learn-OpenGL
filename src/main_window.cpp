#include "main_window.hpp"

MainWindow::MainWindow(GLuint width, GLuint height) {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // mac os specific

    this->window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(this->window, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
}

void MainWindow::SetCursorCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(this->window, callback);
}

void MainWindow::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(this->window, callback);
}

void MainWindow::Current() {
    glfwMakeContextCurrent(this->window);
}
