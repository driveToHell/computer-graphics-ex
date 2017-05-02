//
// Created by Zacks on 2017/4/24.
//

#ifndef _MYSHADER_H_
#define _MYSHADER_H_

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class myShader {
public:
    myShader (const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource);
    
    void use ();

private:
    GLuint shaderProgram;
};

myShader::myShader (const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource) {
    std::string vertexCodeS;
    std::string fragmentCodeS;
    GLint success;
    GLchar infoLog[512];
    std::ifstream vertexShaderFile(vertexShaderSource);
    std::ifstream fragmentShaderFile(fragmentShaderSource);
    std::stringstream vShaderStream, fShaderStream;
    try
    {
        vertexShaderFile.open(vertexShaderSource);
        fragmentShaderFile.open(fragmentShaderSource);
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexCodeS = vShaderStream.str();
        fragmentCodeS = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const GLchar* const vertexCode = vertexCodeS.c_str();
    const GLchar* const fragmentCode = fragmentCodeS.c_str();
    
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 未成功则...
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 未成功则...
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    glLinkProgram(this->shaderProgram);
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void myShader::use () {
    glUseProgram(this->shaderProgram);
}

#endif //_MYSHADER_H
