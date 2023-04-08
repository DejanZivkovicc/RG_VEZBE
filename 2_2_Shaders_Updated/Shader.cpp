//
// Created by kidebratzp on 4/9/23.
//
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "Shader.h"

std::string readFileContents(const char* path){
    std::ifstream in(path);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

Shader::Shader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath){
    std::string vertexShaderSourceString = readFileContents(vertexShaderSourcePath);

    int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = vertexShaderSourceString.c_str();

    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);

    int success;
    char infoLog[512] = {0};
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEX::SHADER: " << infoLog << '\n';
    }

    int fragmentSHaderId = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSourceString = readFileContents(fragmentShaderSourcePath);
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

    glShaderSource(fragmentSHaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentSHaderId);
    glGetShaderiv(fragmentSHaderId, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentSHaderId, 512, NULL, infoLog);
        std::cout << "ERROOR::FRAGMENT::SHADER: " << infoLog << '\n';
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentSHaderId);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER: " << infoLog << '\n';
    }
    m_shaderProgramId = shaderProgram;
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentSHaderId);
}

void Shader::use(){
    assert(m_shaderProgramId > 0);
    glUseProgram(m_shaderProgramId);
}

void Shader::setUniform4f(const char* varName, float v0, float v1, float v2, float v3){
    int varId = glGetUniformLocation(m_shaderProgramId, varName);
    glUniform4f(varId, v0, v1, v2, v3);
}

void Shader::deleteProgram(){
    assert(m_shaderProgramId > 0);
    glDeleteProgram(m_shaderProgramId);
}