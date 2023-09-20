#include <cmath>
#include <string>
#include "Application.h"
#include "Entity.h"
#include "LinearAlgebra.h"

Application::Application()
    : attributeLayouts{
        {3, GL_FLOAT},
        {2, GL_FLOAT},
        {1, GL_FLOAT}
    }, indexCount(0), vertexCount(0)
{
}

void Application::init()
{
    window.init();
    renderer.init();

    entities.reserve(5);
    vertices.reserve(6 * 24);
    indices.reserve(3 * 12);
    modelMatrices.reserve(5);

    projectionMatrix.init(4, 4);
}

Entity* Application::generateEntity()
{
    entities.emplace_back();
    uint32_t entityIndex = entities.size() - 1;
    entities[entityIndex].init(entityIndex, entityIndex);
    return &entities[entityIndex];
}

Entity* Application::getEntity(uint32_t id)
{
    return &entities[id];
}

void Application::setTexture(const std::string& texturePath)
{
    this->texturePath = texturePath;
}

void Application::start()
{
    generateProjectionMatrix();

    const uint32_t vertexSId = renderer.loadShader(GL_VERTEX_SHADER, "./shaders/vertex.glsl");
    const uint32_t fragmentSId = renderer.loadShader(GL_FRAGMENT_SHADER, "./shaders/fragment.glsl");
    const uint32_t programId = renderer.loadProgram();

    renderer.setUniform1i("u_ImageTextureUnit", 0);
    renderer.loadTexture(texturePath, 0);
}

void Application::generateProjectionMatrix()
{
    const float fovScalar = 1.0f / tan(fov / 2.0f);
    const float aspectRatioScalar = 1.0f / ((float)window.getWindowWidth() / (float)window.getWindowHeight());
    const float qScalar = zFar / (zFar - zNear);

    /*
    projectionMatrix.setData({
        aspectRatioScalar * fovScalar, 0.0f, 0.0f, 0.0f,
        0.0f, fovScalar, 0.0f, 0.0f,
        0.0f, 0.0f, -qScalar, -1.0f,
        0.0f, 0.0f, zNear * qScalar, 0.0f
    });
    */
    projectionMatrix.setData({
        aspectRatioScalar * fovScalar, 0.0f, 0.0f, 0.0f,
        0.0f, fovScalar, 0.0f, 0.0f,
        0.0f, 0.0f, -qScalar, zNear * qScalar,
        0.0f, 0.0f, -1.0f, 0.0f
    });
}

void Application::load()
{
    vertices.clear();
    indices.clear();
    modelMatrices.clear();
    vertexCount = 0;
    indexCount = 0;

    for (uint32_t i = 0; i < entities.size(); i++)
    {
        loadEntity(entities[i]);
    }

    renderer.loadBuffer(GL_ARRAY_BUFFER, vertices.data(), sizeof(float) * vertices.size());
    renderer.loadBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.data(), sizeof(uint32_t) * indices.size());
    renderer.loadVertexAttribArray(attributeLayouts, 3);

    
}

void Application::loadEntity(const Entity& entity)
{
    const std::vector<float>& vertices = entity.getVertices();
    for (uint32_t i = 0; i < vertices.size(); i++)
    {
        this->vertices.push_back(vertices[i]);
    }
    
    const std::vector<uint32_t>& indices = entity.getIndices();
    for (uint32_t i = 0; i < indices.size(); i++)
    {
        this->indices.push_back(indices[i] + vertexCount);
    }
    vertexCount += entity.getVertexCount();
    indexCount += indices.size();

    modelMatrices.emplace_back();
    Matrix &modelMatrix = modelMatrices[modelMatrices.size() - 1];
    modelMatrix.init(4, 4);
    modelMatrix.setData(entity.getModelMatrix().getDataCopy());
    modelMatrix = modelMatrix.multiply(projectionMatrix);

    const float *modelMatrixData = modelMatrix.getData().data();
    renderer.setUniformMatrix4fv("transformationMatrices[" + std::to_string(entity.getModelId()) + "]", 1, modelMatrixData);
}

bool Application::shouldLoop()
{
    return window.windowShouldClose();
}

void Application::terminate()
{
    renderer.terminate();
    window.terminate();
}

void Application::draw()
{
    renderer.draw(indexCount);
    window.swapBuffers();
}

void Application::pollEvents()
{
    window.pollEvents();
}