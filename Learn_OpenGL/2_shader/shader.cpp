//
// Created by Zacks on 2017/4/24.
//

#define _NOT_MAIN_

#ifndef _NOT_MAIN_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "myShader.h"

const GLuint winWidth = 800;
const GLuint winHeight = 600;

void error_callback (int, const char *);


int main () {
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    
    auto window = glfwCreateWindow(winWidth, winHeight, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    int vpWidth, vpHeight;
    glfwGetFramebufferSize(window, &vpWidth, &vpHeight);
    glViewport(0, 0, vpWidth, vpHeight);
    
    myShader shader("Learn_OpenGL/res/shader/2_vertexShader.vs", "Learn_OpenGL/res/shader/2_fragmentShader.fs");
    
    GLfloat vertices[] = {
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    GLuint vao, vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)(9* sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    
    glfwTerminate();
    return 0;
}

void error_callback(int error, const char* description){

}
#endif // _NOT_MAIN_