#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();
    void init();
    void terminate();
    void printVersion();

    inline bool windowShouldClose();
    inline void swapBuffers();
    inline void pollEvents();

    inline uint32_t getWindowWidth() const;
    inline uint32_t getWindowHeight() const;

private:
    uint32_t windowWidth;
    uint32_t windowHeight;
    GLFWwindow* glfwWindow;
};

inline bool Window::windowShouldClose()
{
    return glfwWindowShouldClose(glfwWindow);
}

inline void Window::swapBuffers()
{
    glfwSwapBuffers(glfwWindow);
}

inline void Window::pollEvents()
{
    glfwPollEvents();
}

inline uint32_t Window::getWindowWidth() const
{
    return windowWidth;
}

inline uint32_t Window::getWindowHeight() const
{
    return windowHeight;
}