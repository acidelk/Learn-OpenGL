#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.hpp"
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

GLfloat mixed = 0.0f;

int main() {


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // mac os specific
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    Shader shaders("../shaders/shader.vertex",
                   "../shaders/shader.fragment");

    GLfloat vertices[] = {
            /* position */         /* color */          /* texture position */
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    GLuint VBO, VAO, IBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    GLuint texture1, texture2;

    // texxture 1
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int imgWidth, imgHeight;
    unsigned char *image = SOIL_load_image("../img/container.jpg", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);


    // texture 2
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    image = SOIL_load_image("../img/awesomeface.png", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    shaders.Use();
    // set uniform textures for fragment shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    GLint texture_1_location = glGetUniformLocation(shaders.program, "ourTexture1");
    glUniform1i(texture_1_location, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    GLint texture_2_location = glGetUniformLocation(shaders.program, "ourTexture2");
    glUniform1i(texture_2_location, 1);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        GLint mixed_location = glGetUniformLocation(shaders.program, "mixed");
        glUniform1f(mixed_location, mixed);


        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, glm::radians((GLfloat) glfwGetTime() * 40.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        GLint transformer_location = glGetUniformLocation(shaders.program, "transformer");
        glUniformMatrix4fv(transformer_location, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        GLfloat scale = ((sin(glfwGetTime()) / 2) + 1.0f) / 2;
        glm::mat4 scaleMat(1.0f);
        scaleMat = glm::translate(scaleMat, glm::vec3(0.5f, 0.5f, 0.0f));
        scaleMat = glm::scale(scaleMat, glm::vec3(scale, scale, scale));
        glUniformMatrix4fv(transformer_location, 1, GL_FALSE, glm::value_ptr(scaleMat));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        if (mixed >= 1.0f) {
            mixed = 1.0f;
        } else {
            mixed += 0.05f;
        }
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        if (mixed <= 0.0f) {
            mixed = 0.0f;
        } else {
            mixed -= 0.05f;
        }
    }
}