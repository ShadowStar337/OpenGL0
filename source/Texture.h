#pragma once
#include <vector>

class Texture
{
public:
    Texture();
    void init();

    uint32_t loadTexture(const std::string& texturePath, uint32_t textureUnit);
    void terminate();
private:
    std::vector<uint32_t> textureIds;
    
    uint32_t setupTexture(const void* textureBuffer, int32_t width, int32_t height);
};