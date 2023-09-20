#include <GL/glew.h>
#include <string>
#include <cmath>
#include "Entity.h"
#include "AttributeLayout.h"
#include "LinearAlgebra.h"

Entity::Entity()
    : modelId(0), vertexCount(0)
{

}

void Entity::init(uint32_t id, uint32_t modelId)
{
    this->id = id;
    this->modelId = modelId;
    vertices.reserve(6 * 24);
    indices.reserve(3 * 12);
    modelMatrix.init(4, 4);
    modelMatrix.setToIdentity();
}

void Entity::generateCubeVertices()
{
    
    vertices = {
        // left triangles
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, static_cast<float>(modelId),
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, static_cast<float>(modelId),
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, static_cast<float>(modelId),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, static_cast<float>(modelId),

        // right triangles
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, static_cast<float>(modelId),
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, static_cast<float>(modelId),
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, static_cast<float>(modelId),
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, static_cast<float>(modelId),

        // bottom triangles
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, static_cast<float>(modelId),
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f, static_cast<float>(modelId),
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, static_cast<float>(modelId),
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, static_cast<float>(modelId),

        // top triangles
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, static_cast<float>(modelId),
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, static_cast<float>(modelId),
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, static_cast<float>(modelId),
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, static_cast<float>(modelId),

        // back triangles
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, static_cast<float>(modelId),
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, static_cast<float>(modelId),
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, static_cast<float>(modelId),
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, static_cast<float>(modelId),

        // front triangles
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, static_cast<float>(modelId),
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, static_cast<float>(modelId),
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, static_cast<float>(modelId),
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, static_cast<float>(modelId),
    };
    
    vertexCount = 24;

    indices = {
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
}

void Entity::resetModelMatrix()
{
    modelMatrix.setToIdentity();
}

void Entity::scale(float xScale, float yScale, float zScale)
{
    Matrix scaleMatrix = Matrix();
    scaleMatrix.init(4, 4);
    scaleMatrix.setData({
        xScale, 0.0f, 0.0f, 0.0f,
        0.0f, yScale, 0.0f, 0.0f,
        0.0f, 0.0f, zScale, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    modelMatrix = modelMatrix.multiply(scaleMatrix);
}

void Entity::rotate(float xRotation, float yRotation, float zRotation)
{
    Matrix xRotationMatrix = Matrix();
    xRotationMatrix.init(4, 4);
    xRotationMatrix.setData({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, static_cast<float>(cos(xRotation)), static_cast<float>(sin(xRotation)), 0.0f,
        0.0f, static_cast<float>(-sin(xRotation)), static_cast<float>(cos(xRotation)), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    Matrix yRotationMatrix = Matrix();
    yRotationMatrix.init(4, 4);
    yRotationMatrix.setData({
        static_cast<float>(cos(yRotation)), 0.0f, static_cast<float>(-sin(yRotation)), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        static_cast<float>(sin(yRotation)), 0.0f, static_cast<float>(cos(yRotation)), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    Matrix zRotationMatrix = Matrix();
    zRotationMatrix.init(4, 4);
    zRotationMatrix.setData({
        static_cast<float>(cos(zRotation)), static_cast<float>(-sin(zRotation)), 0.0f, 0.0f,
        static_cast<float>(sin(zRotation)), static_cast<float>(cos(zRotation)), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    modelMatrix = modelMatrix.multiply(xRotationMatrix).multiply(yRotationMatrix).multiply(zRotationMatrix);
}

void Entity::translate(float xTranslation, float yTranslation, float zTranslation)
{
    Matrix translationMatrix = Matrix();
    translationMatrix.init(4, 4);
    translationMatrix.setData({
        1.0f, 0.0f, 0.0f, xTranslation,
        0.0f, 1.0f, 0.0f, yTranslation,
        0.0f, 0.0f, 1.0f, zTranslation,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    modelMatrix = modelMatrix.multiply(translationMatrix);
}