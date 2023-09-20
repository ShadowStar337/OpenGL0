#pragma once
#include <GL/glew.h>

void openGLMessage(GLenum source, GLenum type, uint32_t id, GLuint severity, int32_t length, const char* message, const void *userParam)
{
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
        std::cout << message << std::endl;
}