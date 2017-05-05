#define _NOT_MAIN_

#ifndef _NOT_MAIN_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <fstream>


void error_callback (int error, const char *description) {
    fprintf(stderr, "ERROR: %s\n", description);
}

static void escape_callback (GLFWwindow *window, int key, int scancode, int action, int mode) {
    // esc退出
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

const GLchar *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
const GLchar *fragmentShaderSource = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

int main () {
    const GLuint width = 800;
    const GLuint height = 600; // 设置窗口大小
    
    if (!glfwInit()) { throw std::runtime_error("glfwInit failed"); } // 初始化glfw
    // 配置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 版本设置
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile 摒弃废弃api
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS
    
    GLFWwindow *window = glfwCreateWindow(width, height, "Hi Triangle", NULL, NULL); // 创造窗口
    if (!window) { throw std::runtime_error("create window failed"); }
    glfwMakeContextCurrent(window); // 设置上下文
    glfwSetErrorCallback(error_callback); // 设置错误回调函数
    glfwSetKeyCallback(window, escape_callback);
    
    glewExperimental = GL_TRUE; // macOS
    if (glewInit() != GLEW_OK) { throw std::runtime_error("glewInit failed"); } // 初始化glew 如果初始化成功，函数返回0 返回0 返回0
    
    int vp_width, vp_height;
    glfwGetFramebufferSize(window, &vp_width, &vp_height);
    glViewport(0, 0, vp_width, vp_height);
    
    // 顶点着色器
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 第二参数，GLSL源码中的字符串数
    glCompileShader(vertexShader);
    
    // 检测编译是否成功
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 未成功则...
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
    }
    
    // 片段着色器
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 未成功则...
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
    }
    
    GLuint shaderProgram; // Shader Program Object
    shaderProgram = glCreateProgram(); // 创建新的着色器程序并返回程序的ID引用
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // 附加着色器并链接
    
    // 检测link是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); // 删除编译过的Shader，不再需要
    
    // 绘制一个物体的过程
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    //glEnableVertexAttribArray(0);
    //glUseProgram(shaderProgram);
    
    GLfloat vertices[] = { // vertices = vertex复数
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    // 使用VAO Vertex Array Object
    // 绑定VAO，并配置相应的VBO，顶点属性指针
    GLuint VAO, VBO; // Vertex Array Object Vertex Buffer Object
    glGenBuffers(1, &VBO); // 为对象生成ID
    glGenVertexArrays(1, &VAO); // 为对象生成ID
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // GL_ARRAY_BUFFER是VBO的一个buffer类型，可同时绑定不同类型buffer
    // 因为buffer类型和vbo绑定，所以得到buffer类型，就有vbo
    // GL_STATIC_DRAW 数据不会或几乎不会改变
    // GL_DYNAMIC_DRAW 数据会改变很多
    // GL_STREAM_DRAW 数据每次绘制都会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将定义好的vertices复制到buffer的内存中（也就是VBO吧？）
    // 设置如何解释vectices
    // vectexShader里定义了layout(location = 0)，这里的0是顶点属性的位置值，也是这个函数的第一个参数
    // 使用了vec3类型，有三个数值
    // 数值类型
    // 是否需要标准化。这里为什么不需要？
    // 步长。单个数据的长度。如果是紧密排列，可以设置为0让opengl自己判断
    // 缓冲偏移量
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0); // 参数为location
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // 配置完毕，解绑VAO,VBO，以免后面被错误的配置
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 绘制物体
        glUseProgram(shaderProgram); // 激活SPO
        glBindVertexArray(VAO);
        //DRAW SOMETHINGS
        glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制类型。location。顶点数
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
}

#endif