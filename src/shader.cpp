#include "shader.hpp"

Shader::Shader(const GLchar *path, GLuint type) {
    std::string code;
    std::ifstream file;

    try {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "Error while read shader files" << std::endl;
    }

    const GLchar *shader_source = code.c_str();

    GLint success;
    GLchar info_log[512];

    this->id = glCreateShader(type);
    glShaderSource(this->id, 1, &shader_source, nullptr);
    glCompileShader(this->id);

    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->id, 512, NULL, info_log);
        std::cout << "shader compilation failed\n" << info_log << std::endl;
    }
}


