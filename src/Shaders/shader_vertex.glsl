#version 330 core

in vec4 model_coefficients;
in vec4 normal_coefficients;
in vec4 texture_coefficients;
in vec4 color_coefficients;

out vec4 position_world;
out vec4 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define BUNNY 0
#define CUBE 1
uniform int object_id;

void main()
{
    gl_Position = projection * view * model * model_coefficients;
    position_world = model * model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;
}
