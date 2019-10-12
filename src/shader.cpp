#include "shader.h"

Shader::Shader(const GLchar *vertex_path, const GLchar *fragment_path) {
    std::string vertex_code, fragment_code;
    std::ifstream vertex_file, fragment_file;

    try {
        vertex_file.open(vertex_path);
        fragment_file.open(fragment_path);
        std::stringstream vertex_stream, fragment_stream;
        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();
        vertex_file.close();
        fragment_file.close();
        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "Error while read shader files" << std::endl;
    }

    const GLchar *vertex_shader_source = vertex_code.c_str();
    const GLchar *fragment_shader_source = fragment_code.c_str();

    GLuint vertex_shader, fragment_shader;
    GLint success;
    GLchar info_log[512];

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "Vertex shader compilation failed\n" << info_log << std::endl;
    }

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "Vertex shader compilation failed\n" << info_log << std::endl;
    }


    this->program = glCreateProgram();

    glAttachShader(this->program, vertex_shader);
    glAttachShader(this->program, fragment_shader);
    glLinkProgram(this->program);

    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, info_log);
        std::cout << "Shaders link failed\n" << info_log << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::Use() {
    glUseProgram(this->program);
}


