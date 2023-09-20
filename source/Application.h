#pragma once
#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "Entity.h"

class Application
{
public:
    Application();

    void init();
    Entity* generateEntity();
    Entity* getEntity(uint32_t id);
    void setTexture(const std::string& texturePath);
    void start();
    void generateProjectionMatrix();
    void load();
    bool shouldLoop();
    void draw();
    void pollEvents();

    void terminate();
private:
    Window window;
    Renderer renderer;
    std::string texturePath;

    std::vector<Entity> entities;

    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<Matrix> modelMatrices;

    Matrix projectionMatrix;
    AttributeLayout attributeLayouts[3];

    uint32_t indexCount;
    uint32_t vertexCount;

    const float PI = 3.14159265358979323846f;
    const float fov = PI / 3.0f;
    const float zNear = -1.0f;
    const float zFar = -10.0f;

    void loadEntity(const Entity &entity);
};