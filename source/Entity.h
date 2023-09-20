#pragma once
#include <vector>
#include <cstdint>
#include <array>
#include "LinearAlgebra.h"

class Entity
{
public:
    Entity();
    void init(uint32_t id, uint32_t modelId);

    void generateCubeVertices();
    void resetModelMatrix();
    void scale(float xScale, float yScale, float zScale);
    void rotate(float xRotation, float yRotation, float zRotation);
    void translate(float xTranslation, float yTranslation, float zTranslation);

    inline const std::vector<float>& getVertices() const;
    inline const uint32_t getVertexCount() const;
    inline const std::vector<uint32_t>& getIndices() const;
    inline const Matrix& getModelMatrix() const;
    inline const uint32_t getModelId() const;
private:
    uint32_t id;
    uint32_t modelId;
    Matrix modelMatrix;
    std::vector<float> vertices;
    uint32_t vertexCount;
    std::vector<uint32_t> indices;
};

inline const std::vector<float> &Entity::getVertices() const
{
    return vertices;
}

inline const uint32_t Entity::getVertexCount() const
{
    return vertexCount;
}

inline const std::vector<uint32_t> &Entity::getIndices() const
{
    return indices;
}

inline const Matrix& Entity::getModelMatrix() const
{
    return modelMatrix;
}

inline const uint32_t Entity::getModelId() const
{
    return modelId;
}