#pragma once
#include "include/glad/glad.h"

class vertex_array_object {
public:
    vertex_array_object();
    ~vertex_array_object();
private:
    GLuint _handle;
};

vertex_array_object::vertex_array_object() {
    glGenVertexArrays(1, &_handle);
}

vertex_array_object::~vertex_array_object() {
    glDeleteVertexArrays(1, &_handle);
}

