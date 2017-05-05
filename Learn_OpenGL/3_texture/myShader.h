//
// Created by Zacks on 2017/5/4.
//

#ifndef _MYSHADER_H
#define _MYSHADER_H

#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <sstream>

class myShader {
public:
    myShader(const GLchar*, const GLchar*);
    void use();
    GLint getUniformLocation(const char*);
private:
    GLuint program;
};

myShader::myShader (const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath) {
    GLint success;
    GLchar infoLog[512];
    
    std::ifstream vertexShaderFile(vertexShaderPath, std::ios::in|std::ios::binary|std::ios::ate);
    std::ifstream fragmentShaderFile(fragmentShaderPath, std::ios::in|std::ios::binary|std::ios::ate);
    
    vertexShaderFile.seekg(0, std::ios::end);
    fragmentShaderFile.seekg(0, std::ios::end);
    int vSFSize = vertexShaderFile.tellg();
    int fSFSize = fragmentShaderFile.tellg();
    
    char* vertexShaderContent = new char [vSFSize];
    char* fragmentShaderContent = new char [fSFSize];
    
    vertexShaderFile.seekg(0, std::ios::beg);
    vertexShaderFile.read(vertexShaderContent, vSFSize);
    vertexShaderFile.close();
    fragmentShaderFile.seekg(0, std::ios::beg);
    fragmentShaderFile.read(fragmentShaderContent, fSFSize);
    fragmentShaderFile.close();
    // std::cout.write(vertexShaderContent, vSFSize);
    const GLchar* const vertexShaderCode = vertexShaderContent;
    const GLchar* const fragmentShaderCode = fragmentShaderContent;
    
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 未成功则...
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 未成功则...
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }
    
    delete [] vertexShaderContent;
    delete [] fragmentShaderContent;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void myShader::use () {
    glUseProgram(this->program);
}


GLint myShader::getUniformLocation(const GLchar* unifromName) {
    GLint location = glGetUniformLocation(this->program, unifromName);
    return location;
}

#endif //_MYSHADER_H
