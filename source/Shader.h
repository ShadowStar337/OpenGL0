#pragma once

#include <string>
#include <vector>

class ShaderProgram
{
public:
    ShaderProgram();
    void init();
    // ShaderProgram(const std::string &vertexSource, const std::string &fragmentSource);
    uint32_t loadShader(const uint32_t shaderType, const std::string& shaderPath);
    // void loadShaders(const std::string &vertexPath, const std::string &fragmentPath);
    // void addShaders(const std::string &vertexSource, const std::string &fragmentSource);
    uint32_t loadProgram();
    void terminate();
    int32_t getProgramId();
private:
    std::vector<std::string> shaderSources;
    std::vector<uint32_t> shaderIds;
    // std::string vertexSource;
    // std::string fragmentSource;
    int32_t programId;
    void fetchShader(const std::string& shaderPath, std::string& shaderSource);
    uint32_t setupShader(const uint32_t shaderType, const std::string& source) const;
    uint32_t setupProgram();
    bool errorCheckShader(const uint32_t shaderType, const uint32_t shaderId) const;
    bool errorCheckProgram(const uint32_t programId) const;
    void getShaderTypeStr(const uint32_t shaderType, std::string& shaderStr) const;
};
