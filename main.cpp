#include <fstream>
#include <iostream>

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

static std::string read_file(const std::string &path) {
    std::ifstream file(path, std::ios::ate);
    if (!file.is_open()) {
        std::cout << "could not find file " << path << std::endl;
    }

    auto size = file.tellg();
    std::string buf(size, '\0');
    file.seekg(0);
    file.read(&buf[0], size);
    return buf;
}

int main() {
    int result = glfwInit();
    if (result == -1) {
        std::cout << "glfw init failed" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    auto *window = glfwCreateWindow(800, 800, "opengl 3", NULL, NULL);
    if (window == NULL) {
        std::cout << "glfw window createion failed" << std::endl;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);


    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat verticies[] = {
        -0.5f, -0.5f, 0, 0.0f, 0.0f, 0.7f,
        0.5, -0.5f, 0,   0.0f, 0.0f, 0.7f,
        0.5f, 0.5f, 0,   0.0f, 0.0f, 0.7f,
        -0.5f, 0.5f, 0,  0.0f, 0.0f, 0.7f,
    };

    GLfloat verticies_hexagon[] = {
        -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f,
        -0.25f, -0.5f, 0.0f,   0.0f, 0.0f, 0.7f,
        0.25f, -0.5f, 0.0f,   0.0f, 0.0f, 0.7f,
        0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 0.7f,
        0.25f, 0.5f, 0.0f,  0.0f, 0.0f, 0.7f,
        -0.25f, 0.5f, 0.0f,  0.0f, 0.0f, 0.7f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies_hexagon), verticies_hexagon, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint indicies[] = {
        0, 1, 2,
        2, 3, 0,
        0, 3, 5,
        5, 3, 4,
    };
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    std::string vert_src = read_file("shader.vert");
    std::string frag_src = read_file("shader.frag");
    const char *pvert_src = vert_src.c_str();
    const char *pfrag_src = frag_src.c_str();
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert, 1, &pvert_src, NULL);
    glShaderSource(frag, 1, &pfrag_src, NULL);
    glCompileShader(vert);
    glCompileShader(frag);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint scale_loc = glGetUniformLocation(program, "scale");

    glUseProgram(program);
    glClearColor(0, 0, 0, 1);

    float scale = 1.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL);
        //scale += 0.01f;
        //if (scale > 1.0f)
            // scale = 0.0f;
        glUniform1f(scale_loc, scale);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteProgram(program);

    glfwDestroyWindow(window);
    glfwTerminate();
}

