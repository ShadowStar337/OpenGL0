#include <GL/glew.h>
#include <string>
#include "../vendors/stb_image.h"
#include "Texture.h"

Texture::Texture()
{
    
}

void Texture::init()
{
    
}

uint32_t Texture::loadTexture(const std::string& texturePath, uint32_t textureUnit)
{
    stbi_set_flip_vertically_on_load(1);
    int32_t width, height, bpp;
    unsigned char* textureBuffer = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    uint32_t textureId = setupTexture(textureBuffer, width, height);
    textureIds.push_back(textureId);
    if (textureBuffer)
    {
        stbi_image_free(textureBuffer);
    }

    return textureId;
}

uint32_t Texture::setupTexture(const void* textureBuffer, int32_t width, int32_t height)
{
    uint32_t textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

    return textureId;
}

void Texture::terminate()
{
    glDeleteTextures(textureIds.size(), textureIds.data());
}