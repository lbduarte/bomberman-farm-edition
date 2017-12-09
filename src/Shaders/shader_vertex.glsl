#version 330 core

in vec4 position;
in vec4 color;

out vec4 interpolated_color;


void main()
{
    gl_Position = vec4(position);
    interpolated_color = vec4(color);

}
