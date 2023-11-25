#pragma once
#include "option.cpp"
#include <optional>
#include <GLFW/glfw3.h>


class glfw {
public:
    glfw() { }

    ~glfw() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    option<int> init();

    bool should_close();
    void swap_buffers();
private:
    GLFWwindow *_window = nullptr;
};

[[nodiscard]]
option<int> glfw::init() {
    int result = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(800, 800, "opengl 3", NULL, NULL);
    if (_window == nullptr) {
        throw;
    }
    glfwMakeContextCurrent(_window);
    if (result != -1)
        return option<int>(result);
    else
        return option<int>::none();
}

bool glfw::should_close() {
    return glfwWindowShouldClose(_window);
}

void glfw::swap_buffers() {
    glfwSwapBuffers(_window);
}

