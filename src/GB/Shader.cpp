#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

void Shader::load(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode; std::string fragmentCode;
    std::ifstream vShaderFile; std::ifstream fShaderFile;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath); fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf(); fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close(); fShaderFile.close();
        vertexCode = vShaderStream.str(); fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) { std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl; return; }
    const char* vShaderCode = vertexCode.c_str(); const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL); glCompileShader(vertex); checkCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL); glCompileShader(fragment); checkCompileErrors(fragment, "FRAGMENT");
    ID = glCreateProgram();
    glAttachShader(ID, vertex); glAttachShader(ID, fragment); glLinkProgram(ID); checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex); glDeleteShader(fragment);
}
void Shader::use() { glUseProgram(this->ID); }
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
void Shader::setVec3(const std::string &name, const glm::vec3 &value) { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
void Shader::setVec2(const std::string &name, const glm::vec2 &value) { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
void Shader::setInt(const std::string &name, int value) { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setFloat(const std::string &name, float value) { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success; char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) { glGetShaderInfoLog(shader, 1024, NULL, infoLog); std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl; }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) { glGetProgramInfoLog(shader, 1024, NULL, infoLog); std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl; }
    }
}
