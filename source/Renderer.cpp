#include <GL/glew.h>
#include <iostream>
#include <stdint.h>
#include "../vendors/stb_image.h"
#include "Renderer.h"
#include "Debug.h"

Renderer::Renderer()
{
    
}

void Renderer::init()
{
    shaderProgram.init();
    glDebugMessageCallback(openGLMessage, nullptr);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

uint32_t Renderer::loadShader(const uint32_t shaderType, const std::string& shaderSource)
{
    return shaderProgram.loadShader(shaderType, shaderSource);
}

uint32_t Renderer::loadProgram()
{
    return shaderProgram.loadProgram();
}

// void Renderer::loadShaders(const std::string& vertexSource, const std::string& fragmentSource)
// {
//     // shaderProgram.loadShader(GL_VERTEX_SHADER, vertexSource);
//     // shaderProgram.loadShader(GL_FRAGMENT_SHADER, fragmentSource);
//     shaderProgram.loadProgram();
// }

// void Renderer::loadBuffers(const void* vertexArray, const uint32_t vertexSize, const uint32_t vertexArrayCount, const void* indexArray, const uint32_t indexSize, const uint32_t indexArrayCount)
// {
//     this->vertexSize = vertexSize;
//     glGenBuffers(1, &vertexBufferId);
//     glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
//     glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexArrayCount, vertexArray, GL_STATIC_DRAW);

//     this->indexSize = indexSize;
//     glGenBuffers(1, &indexBufferId);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indexArrayCount, indexArray, GL_STATIC_DRAW);
// }

uint32_t Renderer::loadBuffer(const uint32_t target, const void* bufferArray, const uint32_t bufferArraySize)
{
    uint32_t bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(target, bufferId);
    glBufferData(target, bufferArraySize, bufferArray, GL_STATIC_DRAW);
    return bufferId;
}

uint32_t Renderer::getGLTypeSize(const uint32_t type)
{
    switch (type)
    {
        case GL_FLOAT:
            return 4;
    }

    return 0;
}

void Renderer::loadVertexAttribArray(const AttributeLayout* attributeLayouts, const uint32_t attributeLayoutCount)
{
    uint64_t offset = 0;
    uint32_t stride = 0;
    for (uint32_t i = 0; i < attributeLayoutCount; i++)
    {
        const AttributeLayout& attributeLayout = attributeLayouts[i];
        stride += getGLTypeSize(attributeLayout.type) * attributeLayout.count;
    }
    
    for (uint32_t i = 0; i < attributeLayoutCount; i++)
    {
        const AttributeLayout& attributeLayout = attributeLayouts[i];
        
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            attributeLayout.count,
            attributeLayout.type,
            false,
            stride,
            (void*) offset
        );
        std::cout << "i: " << i << std::endl;
        std::cout << "attributeLayout.count: " << attributeLayout.count << std::endl;
        std::cout << "attributeLayout.type: " << attributeLayout.type << " GL_FLOAT: " << GL_FLOAT << std::endl;
        std::cout << "stride: " << stride << std::endl;
        std::cout << "offset: " << (void*)offset << std::endl;
        
        offset += getGLTypeSize(attributeLayout.type) * attributeLayout.count;
    }
}

int32_t Renderer::getUniformLocation(const std::string& uniformName)
{
    int32_t uniformLocation = glGetUniformLocation(shaderProgram.getProgramId(), uniformName.c_str());
    if (uniformLocation == -1)
    {
        std::cout << "[RENDERER]: OpenGL could not find the location of uniform " + uniformName + "." << std::endl;
    }
    
    return uniformLocation;
}

int32_t Renderer::setUniform1f(const std::string& uniformName, float value)
{
    int32_t uniformLocation = getUniformLocation(uniformName);
    glUniform1f(uniformLocation, value);
    return uniformLocation;
}

int32_t Renderer::setUniform1i(const std::string& uniformName, int32_t value)
{
    int32_t uniformLocation = getUniformLocation(uniformName);
    glUniform1i(uniformLocation, value);
    return uniformLocation;
}

int32_t Renderer::setUniformMatrix3fv(const std::string& uniformName, const uint32_t count, const float* value)
{
    int32_t uniformLocation = getUniformLocation(uniformName);
    glUniformMatrix3fv(uniformLocation, count, false, value);
    return uniformLocation;
}

int32_t Renderer::setUniformMatrix4fv(const std::string& uniformName, const uint32_t count, const float* value)
{
    int32_t uniformLocation = getUniformLocation(uniformName);
    glUniformMatrix4fv(uniformLocation, count, false, value);
    return uniformLocation;
}

uint32_t Renderer::loadTexture(const std::string& texturePath, uint32_t textureUnit)
{
    return  texture.loadTexture(texturePath, textureUnit);
}

void Renderer::draw(const uint32_t indexCount)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer::terminate()
{
    shaderProgram.terminate();
    texture.terminate();
}