#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <array>
#include "../vendors/stb_image.h"
#include "Shader.h"
#include "Renderer.h"
#include "Window.h"
#include "Application.h"
#include "Entity.h"
#include "LinearAlgebra.h"
#include "Test.h"

int main(void)
{
    Test test = Test();
    test.matrixMultiplicationTest();

    Application application = Application();
    application.init();
    application.setTexture("./resources/image.png");
    
    for (uint32_t i = 0; i < 20; i++)
    {
        Entity* entity = application.generateEntity();
        entity->generateCubeVertices();
    }
    
    application.start();

    float xRotationsPerSecond = 0.04f;
    float yRotationsPerSecond = 0.08f;
    float zRotationsPerSecond = 0.12f;
    float PI = 3.14159265358979323846264338;

    uint32_t totalFrames = 0;
    uint32_t frames = 0;
    double previousTime = 0.0;

    while (!application.shouldLoop())
    {
        
        // Uniforms are set once per draw
        

        for (uint32_t i = 0; i < 20; i++)
        {
            Entity* entity = application.getEntity(i);
    
            float xFrameStep = totalFrames / 60.0f * xRotationsPerSecond * 2.0f * PI;
            float yFrameStep = totalFrames / 60.0f * yRotationsPerSecond * 2.0f * PI;
            float zFrameStep = totalFrames / 60.0f * zRotationsPerSecond * 2.0f * PI;

            float xStep = cos(static_cast<float>(totalFrames) / 60.0f * 0.05f + (2.0f * PI * i / 20.0f));
            float yStep = sin(static_cast<float>(totalFrames) / 60.0f * 0.05f + (2.0f * PI * i / 20.0f));

            entity->resetModelMatrix();

            entity->scale(0.3f, 0.3f, 0.3f);
            entity->rotate(xFrameStep, yFrameStep, zFrameStep);
            entity->translate(xStep, yStep, -4.0f);
        }

        /*
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
        */
        
        application.load();
        application.draw();

        // int32_t width, height;
        // glfwGetWindowSize(window, &width, &height);
        // std::cout << "Window width:" << width << "Window height:" << height << std::endl;
        totalFrames++;

        application.pollEvents();
        
        frames++;
        if (glfwGetTime() - previousTime > 1.0)
        {
            std::cout << "FPS:" << frames << std::endl;
            previousTime = glfwGetTime();
            frames = 0;
        }
    }

    application.terminate();
    return 0;
}