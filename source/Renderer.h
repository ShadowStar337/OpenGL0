#pragma once
#include "Shader.h"
#include "AttributeLayout.h"

class Renderer
{
public:
    Renderer();
    void init();
    uint32_t loadShader(const uint32_t shaderType, const std::string& shaderSource);
    uint32_t loadProgram();
    // void loadShaders(const std::string& vertexSource, const std::string& fragmentSource);
    uint32_t loadBuffer(const uint32_t target, const void* bufferArray, const uint32_t bufferArraySize);
    // void loadBuffers(const void* vertexArray, const uint32_t vertexSize, const uint32_t vertexArrayCount, const void* indexArray, const uint32_t indexSize, const uint32_t indexArrayCount);
    void loadVertexAttribArray(const AttributeLayout* attributeLayouts, const uint32_t attributeLayoutCount);

    void setUniform1f(const std::string& uniformName, float value);

    void draw(const uint32_t indexCount);
private:
    ShaderProgram shaderProgram;
    // uint32_t vertexBufferId;
    // uint32_t indexBufferId;
    // uint32_t vertexSize;
    // uint32_t indexSize;
    
    uint32_t getGLTypeSize(const uint32_t type);
};