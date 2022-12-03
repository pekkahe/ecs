#version 330
out vec4 FragColor;

in vec4 color;
//in vec3 pos;
//in vec2 texCoord;

void main()
{
    FragColor = color; //vec4(color, 1.0);
}