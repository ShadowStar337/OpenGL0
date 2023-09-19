#pragma once
#include "Shader.h"
#include "AttributeLayout.h"
#include "Texture.h"

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
    uint32_t loadTexture(const std::string& texturePath, uint32_t textureUnit);

    int32_t getUniformLocation(const std::string& uniformName);
    int32_t setUniform1f(const std::string& uniformName, float value);
    int32_t setUniform1i(const std::string& uniformName, int32_t value);
    int32_t setUniformMatrix3fv(const std::string& uniformName, const uint32_t count, const float* value);
    int32_t setUniformMatrix4fv(const std::string& uniformName, const uint32_t count, const float* value);

    void draw(const uint32_t indexCount);
    void terminate();
private:
    ShaderProgram shaderProgram;
    Texture texture;
    
    // uint32_t vertexBufferId;
    // uint32_t indexBufferId;
    // uint32_t vertexSize;
    // uint32_t indexSize;
    
    uint32_t getGLTypeSize(const uint32_t type);
};