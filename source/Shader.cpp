#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Shader.h"

ShaderProgram::ShaderProgram()
{
    
}

void ShaderProgram::init()
{
    shaderSources.reserve(2);
}

// ShaderProgram::ShaderProgram(const std::string &vertexSource, const std::string &fragmentSource)
//     : vertexSource(vertexSource), fragmentSource(fragmentSource)
// {

// }

uint32_t ShaderProgram::loadProgram()
{
    uint32_t programId = setupProgram();
    glUseProgram(programId);
    return programId;
}

uint32_t ShaderProgram::loadShader(const uint32_t shaderType, const std::string& shaderPath)
{
    shaderSources.push_back("");
    std::string& shaderSource = shaderSources[shaderSources.size() - 1];
    
    fetchShader(shaderPath, shaderSource);
    uint32_t shaderId = setupShader(shaderType, shaderSource);
    shaderIds.push_back(shaderId);
    return shaderId;
}

// void ShaderProgram::loadShaders(const std::string& vertexPath, const std::string& fragmentPath)
// {
//     fetchShader(vertexPath, vertexSource);
//     fetchShader(fragmentPath, fragmentSource);
// }

void ShaderProgram::fetchShader(const std::string& shaderPath, std::string& shaderSource)
{
    std::ifstream inputFStream(shaderPath);
    
    std::string line;
    while (getline(inputFStream, line))
    {
        shaderSource += line + "\n";
    }
}

// void ShaderProgram::addShaders(const std::string& vertexSource, const std::string& fragmentSource)
// {
//     this->vertexSource = vertexSource;
//     this->fragmentSource = fragmentSource;
// }

uint32_t ShaderProgram::setupProgram()
{
    programId = glCreateProgram();

    for (uint32_t i = 0; i < shaderIds.size(); i++)
    {
        uint32_t shaderId = shaderIds[i];
        glAttachShader(programId, shaderId);
    }
    
    glLinkProgram(programId);
    glValidateProgram(programId);

    for (uint32_t i = 0; i < shaderIds.size(); i++)
    {
        uint32_t shaderId = shaderIds[i];
        glDeleteShader(shaderId);
    }

    if (errorCheckProgram(programId))
    {
        return 0;
    }
    
    return programId;
}

uint32_t ShaderProgram::setupShader(const uint32_t shaderType, const std::string &source) const
{
    const uint32_t shaderId = glCreateShader(shaderType);
    const char *sourceCStr = source.c_str();
    glShaderSource(shaderId, 1, &sourceCStr, nullptr);
    glCompileShader(shaderId);

    if (errorCheckShader(shaderType, shaderId))
    {
        return 0;
    }
    return shaderId;
}

bool ShaderProgram::errorCheckProgram(const uint32_t programId) const
{
    int32_t result;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int32_t length;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);

        char *message = new char[length];
        glGetProgramInfoLog(programId, length, &length, message);

        std::cout << "Error message for shader program: " << std::endl;
        std::cout << message << std::endl;

        glDeleteProgram(programId);
        delete[] message;

        return true;
    }

    return false;
}

bool ShaderProgram::errorCheckShader(const uint32_t shaderType, const uint32_t shaderId) const
{
    int32_t result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int32_t length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(shaderId, length, &length, message);

        std::string shaderStr;
        getShaderTypeStr(shaderType, shaderStr);
        std::cout << "Error message for " + shaderStr + ":" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(shaderId);
        delete[] message;

        return true;
    }

    return false;
}

void ShaderProgram::getShaderTypeStr(const uint32_t shaderType, std::string &shaderStr) const
{
    switch (shaderType)
    {
        case GL_VERTEX_SHADER:
            shaderStr = "GL_VERTEX_SHADER";
            return;
        case GL_FRAGMENT_SHADER:
            shaderStr = "GL_FRAGMENT_SHADER";
            return;
    }
}

int32_t ShaderProgram::getProgramId()
{
    return programId;
}

void ShaderProgram::terminate()
{
    
}