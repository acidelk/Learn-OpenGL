#include "program.hpp"

Program::Program() {
    this->id = glCreateProgram();
}

void Program::AttachShader(Shader shader) {
    this->shaders.push_back(shader.id);
    glAttachShader(this->id, shader.id);
}

void Program::Use() {
    glUseProgram(this->id);
}

void Program::Link() {
    glLinkProgram(this->id);

    GLint success;
    GLchar info_log[512];
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->id, 512, nullptr, info_log);
        std::cout << "Shaders link failed\n" << info_log << std::endl;
    }

    std::for_each(shaders.begin(), shaders.end(), [](GLuint &shaderId) { glDeleteShader(shaderId); });
}
