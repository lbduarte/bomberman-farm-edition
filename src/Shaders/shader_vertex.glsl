#version 330 core

in vec4 model_coefficients;
in vec4 normal_coefficients;
in vec2 texture_coefficients;
in vec4 color_coefficients;

out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define PLAN 0
#define CUBE 1
uniform int object_id;

void main()
{
    gl_Position = projection * view * model * model_coefficients;

    // Posição do vértice atual no sistema de coordenadas global (World).
    position_world = model * model_coefficients;

    // Posição do vértice atual no sistema de coordenadas local do modelo.
    position_model = model_coefficients;

    // Normal do vértice atual no sistema de coordenadas global (World).
    // Veja slide 94 do documento "Aula_07_Transformacoes_Geometricas_3D.pdf".
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    // Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
    texcoords = texture_coefficients;
}
