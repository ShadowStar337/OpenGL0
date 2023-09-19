#version 330 core

in vec4 vertexOutput;
layout (location = 0) out vec4 color;

const float Pi = 3.142f;
uniform float u_Rotation;

// HSL to RGB formula from https://www.baeldung.com/cs/convert-color-hsl-rgb
/*
void main()
{
    float angle = atan(vertexOutput.y, vertexOutput.x) + u_Rotation;
    angle = mod(angle, 2.0 * Pi);
    float saturation = 1.0f;
    float lightness = 0.5f;

    float chroma = (1.0f - abs(2.0f * lightness - 1.0f)) * saturation;
    float hueTick = angle / (Pi / 3.0f);
    float x = chroma * (1.0f - abs(mod(hueTick, 2.0f) - 1.0f));

    float red1;
    float green1;
    float blue1;

    if (hueTick <= 1.0f)
    {
        red1 = chroma;
        green1 = x;
        blue1 = 0.0f;
    }
    else if (hueTick <= 2.0f)
    {
        red1 = x;
        green1 = chroma;
        blue1 = 0.0f;
    }
    else if (hueTick <= 3.0f)
    {
        red1 = 0.0f;
        green1 = chroma;
        blue1 = x;
    }
    else if (hueTick <= 4.0f)
    {
        red1 = 0.0f;
        green1 = x;
        blue1 = chroma;
    }
    else if (hueTick <= 5.0f)
    {
        red1 = x;
        green1 = 0.0f;
        blue1 = chroma;
    }
    else if (hueTick <= 6.0f)
    {
        red1 = chroma;
        green1 = 0.0f;
        blue1 = x;
    }

    float m = lightness - chroma / 2.0f;

    float red = red1 + m;
    float green = green1 + m;
    float blue = blue1 + m;

    color = vec4(red, green, blue, 1.0f);
}
*/

void main()
{
    float angle = atan(vertexOutput.y, vertexOutput.x) + u_Rotation;
    angle = mod(angle, 2.0 * Pi);

    color = vec4(0.0, angle / (2.0 * Pi), 0.0, 1.0f);
}


// ------------------------------------------------------------

/*
void main()
{
    float vertexX = (vertexOutput.x + 1.0f) / 2.0f;
    float vertexY = (vertexOutput.y + 1.0f) / 2.0f;

    float red = (vertexX + (1.0f - vertexY)) / 2.0f;
    float green = (vertexX + vertexY) / 2.0f;
    float blue = ((1.0f - vertexX) + vertexY) / 2.0f;
    color = vec4(red, green, blue, 1.0);
    // color = vec4(red * u_ColorBrightness.x, green * u_ColorBrightness.y, blue * u_ColorBrightness.z, 1.0 * u_ColorBrightness.w);
}
*/