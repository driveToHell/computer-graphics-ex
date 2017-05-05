//
// Created by Zacks on 2017/5/4.
//

//#define NOT_MAIN
#ifndef NOT_MAIN

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "myShader.h"
#include <SOIL.h>

void error_callback(int error, const GLchar* description);

int main()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    
    auto window = glfwCreateWindow(800, 600, "Texture", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glViewport(0, 0, 799, 599);
    
    myShader shader("Learn_OpenGL/res/shader/3_vertexShader.vs", "Learn_OpenGL/res/shader/3_fragmentShader.fs");
    
    // 生成纹理对象
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 设置环绕，过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // SOIL载入图像
    int width, height;
    unsigned char* image = SOIL_load_image("Learn_OpenGL/res/picture/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    // 生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    GLint samplerPosition = shader.getUniformLocation("ourTexture");
    
    GLfloat vertices[] = {
    //      ----位置--------||-----颜色-------||---纹理坐标--
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // 右上
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// 左下
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上
    };
    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_VERTEX_ARRAY, vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*(sizeof(GLfloat)), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*(sizeof(GLfloat)), (void*)(3*sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*(sizeof(GLfloat)), (void*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    while(!glfwWindowShouldClose(window)){
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    
        glBindTexture(GL_TEXTURE_2D, texture);
        shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}

void error_callback(int error, const GLchar* description) {

}
#endif