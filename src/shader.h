#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader {
public:
    GLuint program{};

    Shader(const GLchar *vertex_path, const GLchar *fragment_path);

    void Use();
};

#endif
