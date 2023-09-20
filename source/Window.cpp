#include <iostream>
#include <GL/glew.h>
#include "Window.h"

Window::Window()
    : windowWidth(1920), windowHeight(1080)
{

}

void Window::init()
{
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed." << std::endl;
        return;
    }

    glfwWindow = glfwCreateWindow(windowWidth, windowHeight, "GLFW Window", NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        std::cout << "GLFW window creation failed." << std::endl;
        return;
    }

    glfwMakeContextCurrent(glfwWindow);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW failed." << std::endl;
        return;
    }

    printVersion();
}

void Window::printVersion()
{
    int32_t majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    std::cout << "OpenGL " << majorVersion << "." << minorVersion << std::endl;
}

void Window::terminate()
{
    glfwTerminate();
}