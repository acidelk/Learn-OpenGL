#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class MainWindow {
public:
    GLFWwindow *window;

    MainWindow(GLuint width, GLuint height);

    void SetCursorCallback(GLFWcursorposfun callback);

    void SetKeyCallback(GLFWkeyfun callback);

    void Current();

};


#endif //WINDOW_HPP
