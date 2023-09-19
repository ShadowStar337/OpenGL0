#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed." << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "GLFW Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "GLFW window creation failed." << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW failed." << std::endl;
    }

    float positions[2 * 4] = {
         1.00f,  1.00f,
        -1.00f,  1.00f,
        -1.00f, -1.00f,
         1.00f, -1.00f
    };

    uint32_t indices[3 * 2] = {
        0, 1, 2,
        2, 3, 0
    };

    AttributeLayout positionLayout[1] = {
        { 2, GL_FLOAT, false }
    };

    Renderer renderer = Renderer();
    renderer.init();
    const uint32_t vertexSId = renderer.loadShader(GL_VERTEX_SHADER, "./shaders/vertex.glsl");
    const uint32_t fragmentSId = renderer.loadShader(GL_FRAGMENT_SHADER, "./shaders/fragment.glsl");
    const uint32_t programId = renderer.loadProgram();
    renderer.loadBuffer(GL_ARRAY_BUFFER, positions, sizeof(float) * 2 * 4);
    renderer.loadBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(uint32_t) * 3 * 2);
    // renderer.loadBuffers(positions, sizeof(float) * 2, 4, indices, sizeof(uint32_t) * 3, 2);
    renderer.loadVertexAttribArray(positionLayout, 1);
    renderer.setUniform1f("u_Rotation", 0.0f);
    

    float rotation = 0.0f;

    double previousTime = 0.0;
    uint32_t frames = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        frames++;
        if (glfwGetTime() - previousTime > 1.0)
        {
            std::cout << "FPS:" << frames << std::endl;
            previousTime = glfwGetTime();
            frames = 0;
        }
        
        /* Render here */
        
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // Uniforms are set once per draw
        // glUniform1f(location, rotation);
        renderer.setUniform1f("u_Rotation", rotation);
        rotation -= 0.002f;
        renderer.draw(3 * 2);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // int32_t width, height;
        // glfwGetWindowSize(window, &width, &height);
        // std::cout << "Window width:" << width << "Window height:" << height << std::endl;
    }

    glfwTerminate();
    return 0;
}
