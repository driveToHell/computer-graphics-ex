//
// Created by Zacks on 2017/4/23.
//

#define _NOT_MAIN_

#ifndef _NOT_MAIN_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

void error_callback (int, const char *);

const GLchar* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
        "}\n\0";

const GLchar* fragmentShaderSourceYellow = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";
const GLchar* fragmentShaderSourceGreen = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";

int main () {
    const GLuint width = 800;
    const GLuint height = 600;
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    glfwSetErrorCallback(error_callback);
    auto window = glfwCreateWindow(width, height, "ex_triangle", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    int vp_width, vp_height;
    glfwGetFramebufferSize(window, &vp_width, &vp_height);
    glViewport(0, 0, vp_width, vp_height);
    
    
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    GLuint fragmentShaderYellow, fragmentShaderGreen;
    fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, nullptr);
    glCompileShader(fragmentShaderGreen);
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, nullptr);
    glCompileShader(fragmentShaderYellow);
    
    GLuint shaderProgramYellow, shaderProgramGreen;
    shaderProgramGreen = glCreateProgram();
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramGreen, vertexShader);
    glAttachShader(shaderProgramGreen, fragmentShaderGreen);
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramGreen);
    glLinkProgram(shaderProgramYellow);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderGreen);
    glDeleteShader(fragmentShaderYellow);
    
    GLfloat vertices1[] = {
            -0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.0f, 0.0f, 0.0f,
    };
    GLfloat vertices2[] = {
            0.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };
    GLfloat vertices3[] = {
            0.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
    };
    GLuint indices[] = {
            0, 1, 3,
            0, 2, 3
    };
    GLuint VAO[3], VBO[3], EBO;
    glGenBuffers(3, VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(3, VAO);
    
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgramGreen);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    glDeleteBuffers(2, VBO);
    glDeleteVertexArrays(2, VAO);
    
    glfwTerminate();
    
    return 0;
    
}

void error_callback (int error, const char *log) {
    fprintf(stderr, "ERROR: %s\n", log);
}
#endif