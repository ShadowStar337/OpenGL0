#version 330 core

layout (location = 0) in vec4 position;
out vec4 vertexOutput;

void main()
{
    gl_Position = position;
    vertexOutput = position;
}