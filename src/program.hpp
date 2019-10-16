#ifndef PROGRAM_HPP
#define PROGRAM_HPP


#include <GL/glew.h>
#include <vector>
#include "shader.hpp"

class Program {
public:
    GLuint id;

    Program();

    void AttachShader(Shader shader);

    void Link();

    void Use();

private:
    std::vector<GLuint> shaders;
};


#endif //PROGRAM_HPP
