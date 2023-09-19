#pragma once

void openGLMessage(GLenum source, GLenum type, uint32_t id, GLuint severity, int32_t length, const char* message, const void *userParam)
{
    std::cout << message << std::endl;
}