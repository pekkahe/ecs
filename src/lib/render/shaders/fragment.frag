#version 330 core
out vec4 FragColor;

in vec4 outColor;
in vec3 outPos;

void main()
{
    FragColor = outColor; // vec4(outPos, 1.0);
}