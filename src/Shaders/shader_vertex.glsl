#version 330 core

in vec4 position;

out vec4 interpolated_color;


void main()
{


    gl_Position = vec4(position);
    interpolated_color = vec4(0.0, 0.0, 1.0, 1.0);

}
