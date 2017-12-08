#version 330 core

in vec4 interpolated_color;

out vec4 color;

void main()
{
    // Definimos a cor final de cada fragmento utilizando a cor interpolada
    // pelo rasterizador.

    color = interpolated_color;
}
