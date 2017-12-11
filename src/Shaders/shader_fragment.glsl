#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpola��o da cor de cada v�rtice, definidas em "shader_vertex.glsl" e
// "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posi��o do v�rtice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no c�digo C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define FLOOR 0
#define WALL 1
#define CUBE 2

uniform int object_id;

// Par�metros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Vari�veis para acesso das imagens de textura
uniform sampler2D Grass;
uniform sampler2D Fence;

// O valor de sa�da ("out") de um Fragment Shader � a cor final do fragmento.
out vec3 color;

void main()
{
    // Obtemos a posi��o da c�mera utilizando a inversa da matriz que define o
    // sistema de coordenadas da c�mera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual � coberto por um ponto que percente � superf�cie de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posi��o no
    // sistema de coordenadas global (World coordinates). Esta posi��o � obtida
    // atrav�s da interpola��o, feita pelo rasterizador, da posi��o de cada
    // v�rtice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada v�rtice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em rela��o ao ponto atual.
    vec4 l = normalize(vec4(0.0,2.0,1.0,0.0));
    vec4 ponto_l = vec4(0.0,2.0,1.0,1.0);

    // Vetor que define o sentido da c�mera em rela��o ao ponto atual.
    vec4 dir_v = normalize(vec4(0.0,-1.0,0.0,0.0));
    vec4 v = normalize(camera_position-p);


    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    float cos_alfa = sqrt(3)/2;

    // Vetor que define o sentido da reflex�o especular ideal.
    vec4 r = -l + 2 * n * (dot(n,l)); // PREENCHA AQUI o vetor de reflex�o especular ideal

    // Par�metros que definem as propriedades espectrais da superf�cie
    vec3 Kd; // Reflet�ncia difusa
    vec3 Ks; // Reflet�ncia especular
    vec3 Ka; // Reflet�ncia ambiente
    float q; // Expoente especular para o modelo de ilumina��o de Phong

    vec3 Kd0;

    // Equa��o de Ilumina��o
    float lambert;
    switch(object_id){
        case WALL:
            U = texcoords.x;
            V = texcoords.y;

            // Obtemos a reflet�ncia difusa a partir da leitura da imagem TextureImage0
            Kd0 = texture(Fence, vec2(U,V)).rgb;

            // Equa��o de Ilumina��o
            lambert = max(0,dot(n,l));

            color = Kd0 * (lambert + 0.01);
            break;

        case FLOOR:
            U = texcoords.x;
            V = texcoords.y;

            // Obtemos a reflet�ncia difusa a partir da leitura da imagem TextureImage0
            Kd0 = texture(Grass, vec2(U,V)).rgb;

            // Equa��o de Ilumina��o
            lambert = max(0,dot(n,l));

            color = Kd0 * (lambert + 0.01);

            break;

        case CUBE:
            break;
    }
    // Cor final com corre��o gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}
