#version 330 core

in vec2 v_TextureCoordinates;
layout (location = 0) out vec4 color;

const float Pi = 3.142f;
uniform float u_Rotation;
uniform sampler2D u_ImageTextureUnit;

void main()
{
    vec4 imageTexColor = texture(u_ImageTextureUnit, v_TextureCoordinates);
    color = imageTexColor;
}