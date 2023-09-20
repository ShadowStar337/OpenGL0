#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in float modelId;

out vec2 v_TextureCoordinates;

uniform mat4x4 transformationMatrices[256];

void main()
{
    /*
    if (position.w == 1.0f)
    {
        if (gl_VertexID % 3 == 0)
        {
            gl_Position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (gl_VertexID % 3 == 1)
        {
            gl_Position = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            gl_Position = vec4(1.0f, 1.0f, 0.0f, 1.0f);
        }
    }
    else
    {
        if (gl_VertexID % 3 == 0)
        {
            gl_Position = vec4(-0.5f, 0.0f, 0.0f, 1.0f);
        }
        else if (gl_VertexID % 3 == 1)
        {
            gl_Position = vec4(-1.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            gl_Position = vec4(-1.0f, -1.0f, 0.0f, 1.0f);
        }
        
    }
    */
    gl_Position = transformationMatrices[int(modelId)] * position;
    v_TextureCoordinates = textureCoordinates;
}