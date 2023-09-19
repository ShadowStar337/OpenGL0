#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "../vendors/stb_image.h"
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

    int32_t majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    std::cout << "OpenGL " << majorVersion << "." << minorVersion << std::endl;

    float positions[5 * 24] = {
        // left triangles
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        // right triangles
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        // bottom triangles
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        // top triangles
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

        // back triangles
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        // front triangles
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    uint32_t indices[3 * 12] = {
        0 + 4 * 0, 1 + 4 * 0, 2 + 4 * 0,
        0 + 4 * 0, 3 + 4 * 0, 1 + 4 * 0,

        0 + 4 * 1, 1 + 4 * 1, 2 + 4 * 1,
        0 + 4 * 1, 3 + 4 * 1, 1 + 4 * 1,

        0 + 4 * 2, 1 + 4 * 2, 2 + 4 * 2,
        0 + 4 * 2, 3 + 4 * 2, 1 + 4 * 2,

        0 + 4 * 3, 1 + 4 * 3, 2 + 4 * 3,
        0 + 4 * 3, 3 + 4 * 3, 1 + 4 * 3,

        0 + 4 * 4, 1 + 4 * 4, 2 + 4 * 4,
        0 + 4 * 4, 3 + 4 * 4, 1 + 4 * 4,

        0 + 4 * 5, 1 + 4 * 5, 2 + 4 * 5,
        0 + 4 * 5, 3 + 4 * 5, 1 + 4 * 5
    };

    float PI = 3.142f;
    float fov = PI / 3.0f;
    float zNear = -1.0f;
    float zFar = -10.0f;
    
    float fovScalar = 1.0f / tan(fov / 2.0f);
    float aspectRatioScalar = 1.0f / (1920.0 / 1080.0);
    float qScalar = zFar / (zFar - zNear);
    
    float projectionMatrix[4 * 4] = {
        aspectRatioScalar * fovScalar, 0.0f, 0.0f, 0.0f,
        0.0f, fovScalar, 0.0f, 0.0f,
        0.0f, 0.0f, -qScalar, -1.0f,
        0.0f, 0.0f, zNear * qScalar, 0.0f
    };

    float xRotationsPerSecond = 0.01f;
    float yRotationsPerSecond = 0.02f;
    float zRotationsPerSecond = 0.03f;

    AttributeLayout positionLayout = { 3, GL_FLOAT };
    AttributeLayout textureLayout = { 2, GL_FLOAT };
    AttributeLayout attributeLayouts[2] = { positionLayout, textureLayout };

    Renderer renderer = Renderer();
    renderer.init();
    
    const uint32_t vertexSId = renderer.loadShader(GL_VERTEX_SHADER, "./shaders/vertex.glsl");
    const uint32_t fragmentSId = renderer.loadShader(GL_FRAGMENT_SHADER, "./shaders/fragment.glsl");
    const uint32_t programId = renderer.loadProgram();
    
    renderer.loadBuffer(GL_ARRAY_BUFFER, positions, sizeof(float) * 5 * 24);
    renderer.loadBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(uint32_t) * 3 * 12);
    renderer.loadVertexAttribArray(attributeLayouts, 2);
    
    renderer.setUniform1i("u_GlobalVars.windowWidth", 480);
    renderer.setUniform1i("u_GlobalVars.windowHeight", 270);
    renderer.setUniformMatrix4fv("u_GlobalVars.projectionMatrix", 1, projectionMatrix);
    
    renderer.setUniform1i("u_ImageTextureUnit", 0);
    renderer.loadTexture("./resources/image.png", 0);

    uint32_t totalFrames = 0;

    double previousTime = 0.0;
    uint32_t frames = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // Uniforms are set once per draw
        // glUniform1f(location, rotation);
        // renderer.setUniform1f("u_Rotation", rotation);
        float xFrameStep = totalFrames / 60.0f * xRotationsPerSecond * 2.0f * PI;
        float yFrameStep = totalFrames / 60.0f * yRotationsPerSecond * 2.0f * PI;
        float zFrameStep = totalFrames / 60.0f * zRotationsPerSecond * 2.0f * PI;

        float xRotationMatrix[3 * 3] = {
            1.0f, 0.0f, 0.0f,
            0.0f, (float)cos(xFrameStep), (float)sin(xFrameStep),
            0.0f, (float)-sin(xFrameStep), (float)cos(xFrameStep)
        };

        float yRotationMatrix[3 * 3] = {
            (float)cos(yFrameStep), 0.0f, (float)-sin(yFrameStep),
            0.0f, 1.0f, 0.0f,
            (float)sin(yFrameStep), 0.0f, (float)cos(yFrameStep)
        };

        float zRotationMatrix[3 * 3] = {
            (float)cos(zFrameStep), (float)sin(zFrameStep), 0.0f,
            (float)-sin(zFrameStep), (float)cos(zFrameStep), 0.0f,
            0.0f, 0.0f, 1.0f
        };
        renderer.setUniformMatrix3fv("u_FrameVars.xRotation", 1, xRotationMatrix);
        renderer.setUniformMatrix3fv("u_FrameVars.yRotation", 1, yRotationMatrix);
        renderer.setUniformMatrix3fv("u_FrameVars.zRotation", 1, zRotationMatrix);
        renderer.draw(3 * 12);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // int32_t width, height;
        // glfwGetWindowSize(window, &width, &height);
        // std::cout << "Window width:" << width << "Window height:" << height << std::endl;
        totalFrames++;
        
        frames++;
        if (glfwGetTime() - previousTime > 1.0)
        {
            std::cout << "FPS:" << frames << std::endl;
            previousTime = glfwGetTime();
            frames = 0;
        }
    }

    renderer.terminate();

    glfwTerminate();
    return 0;
}
