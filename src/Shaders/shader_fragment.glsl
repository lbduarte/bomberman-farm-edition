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
#define HAYCUBE 2
#define WOODCUBE 3
#define COW 4

uniform int object_id;

// Vari�veis para acesso das imagens de textura
uniform sampler2D Grass;
uniform sampler2D Fence;
uniform sampler2D HayCube;
uniform sampler2D WoodCube;

// O valor de sa�da ("out") de um Fragment Shader � a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

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
    vec4 l = normalize(camera_position - p);

    // Vetor que define o sentido da c�mera em rela��o ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflex�o especular ideal.
    vec4 r = -l + 2 * n * (dot(n,l));

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    vec3 Kd0;

    if(object_id == WALL){
        U = texcoords.x;
        V = texcoords.y;

        // Obtemos a reflet�ncia difusa a partir da leitura da imagem TextureImage0
        Kd0 = texture(Fence, vec2(U,V)).rgb;

        // Equa��o de Ilumina��o
        // float lambert = max(0,dot(n,l));
        float lambert = 1;
        color = Kd0 * (lambert + 0.01);
    }
    else if(object_id == FLOOR){
        U = texcoords.x;
        V = texcoords.y;

        // Obtemos a reflet�ncia difusa a partir da leitura da imagem TextureImage0
        Kd0 = texture(Grass, vec2(U,V)).rgb;

        // Equa��o de Ilumina��o
        // float lambert = max(0,dot(n,l));
        float lambert = 1;
        color = Kd0 * (lambert + 0.01);
    }
    else if(object_id == WOODCUBE)
    {
        float minx = -0.5;
        float maxx = 0.5;

        float miny = -0.5;
        float maxy = 0.5;

        float minz = -0.5;
        float maxz = 0.5;

        float largura = maxx-minx;
        float altura = maxy-miny;

        if(position_model.z==0.5 || position_model.z==-0.5)
        {
            U = (position_model.x-minx)/largura;
            V = (position_model.y-miny)/altura;
        }
        else if(position_model.x==0.5 || position_model.x==-0.5)
        {
            U = (position_model.z-minx)/largura;
            V = (position_model.y-miny)/altura;
        }
        else if(position_model.y==0.5 || position_model.y==-0.5)
        {
            U = (position_model.x-minx)/largura;
            V = (position_model.z-miny)/altura;
        }

        // Obtemos a reflet�ncia difusa a partir da leitura da imagem TextureImage0
        Kd0 = texture(WoodCube, vec2(U,V)).rgb;

        // Equa��o de Ilumina��o
        // float lambert = max(0,dot(n,l));
        float lambert = 1;
        color = Kd0 * (lambert + 0.01);
    }
    else if(object_id == HAYCUBE)
    {
        float minx = -0.5;
        float maxx = 0.5;

        float miny = -0.5;
        float maxy = 0.5;

        float minz = -0.5;
        float maxz = 0.5;

        float largura = maxx-minx;
        float altura = maxy-miny;


        if(position_model.z==0.5 || position_model.z==-0.5)
        {
            U = (position_model.x-minx)/largura;
            V = (position_model.y-miny)/altura;
        }
        else if(position_model.x==0.5 || position_model.x==-0.5)
        {
            U = (position_model.z-minx)/largura;
            V = (position_model.y-miny)/altura;
        }
        else if(position_model.y==0.5 || position_model.y==-0.5)
        {
            U = (position_model.x-minx)/largura;
            V = (position_model.z-miny)/altura;
        }

        // Obtemos a reflet�ncia difusa a partir da leitura da imagem TextureImage0
        Kd0 = texture(HayCube, vec2(U,V)).rgb;

        // Equa��o de Ilumina��o
        // float lambert = max(0,dot(n,l));
        float lambert = 1;
        color = Kd0 * (lambert + 0.01);

    }
    else if(object_id == COW)
    {
        // Propriedades espectrais da vaca
        vec3 Kd = vec3(0.2,0.1,0.06);
        vec3 Ks = vec3(0.8,0.8,0.8);
        vec3 Ka = Kd/2;
        float q = 32.0;

        // Espectro da fonte de ilumina��o
        vec3 I = vec3(1.0,1.0,1.0);

        // Espectro da luz ambiente
        vec3 Ia = vec3(0.2,0.2,0.2);

        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = Kd * I * max(0.0,dot(n,l));

        // Termo ambiente
        vec3 ambient_term = Ka * Ia;

        // Termo especular utilizando o modelo de ilumina��o de Phong
        vec3 phong_specular_term  = Ks * I * pow(max(0.0,dot(r,v)), q);

        color = lambert_diffuse_term + ambient_term + phong_specular_term;
    }
    // Cor final com corre��o gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}
