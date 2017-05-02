#version 330 core
in vec3 customColor;
out vec4 color;
void main()
{
    color = vec4(customColor, 1.0f);
}