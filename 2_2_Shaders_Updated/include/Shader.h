//
// Created by kidebratzp on 4/9/23.
//

#ifndef INC_2_1_SHADERS_SHADER_H
#define INC_2_1_SHADERS_SHADER_H


class Shader {
    unsigned m_shaderProgramId;
public:
    Shader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
    void use();
    void setUniform4f(const char* varName, float v0, float v1, float v2, float v3);
    void deleteProgram();
};


#endif //INC_2_1_SHADERS_SHADER_H
