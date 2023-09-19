#version 330 core

struct GlobalVars
{
    int windowWidth;
    int windowHeight;
    mat4x4 projectionMatrix;
};

struct FrameVars
{
    mat3x3 xRotation;
    mat3x3 yRotation;
    mat3x3 zRotation;
};

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinates;

out vec2 v_TextureCoordinates;

uniform GlobalVars u_GlobalVars;
uniform FrameVars u_FrameVars;

void main()
{
    vec3 xRotatedVertex = u_FrameVars.xRotation * position.xyz;
    vec3 xyRotatedVertex = u_FrameVars.yRotation * xRotatedVertex;
    vec3 xyzRotatedVertex = u_FrameVars.zRotation * xyRotatedVertex;
    xyzRotatedVertex[2] -= 4.0f;

    vec4 projectedVertex = u_GlobalVars.projectionMatrix * vec4(xyzRotatedVertex.x, xyzRotatedVertex.y, xyzRotatedVertex.z, 1.0f);

    gl_Position = projectedVertex;

    v_TextureCoordinates = textureCoordinates;
}