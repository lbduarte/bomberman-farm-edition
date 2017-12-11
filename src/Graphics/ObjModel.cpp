#include "ObjModel.h"

using namespace Graphics;
// Este construtor l� o modelo de um arquivo utilizando a biblioteca tinyobjloader.
// Veja: https://github.com/syoyo/tinyobjloader
ObjModel::ObjModel(const char* filename, const char* basepath, bool triangulate)
{
    printf("Carregando modelo \"%s\"... ", filename);

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);

    if (!err.empty())
        fprintf(stderr, "\n%s\n", err.c_str());

    if (!ret)
        throw std::runtime_error("Erro ao carregar modelo.");

    printf("OK.\n");
}

// Fun��o que computa as normais de um ObjModel, caso elas n�o tenham sido
// especificadas dentro do arquivo ".obj"
void ObjModel::computeNormals()
{
    if ( !this->attrib.normals.empty() )
        return;

    // Primeiro computamos as normais para todos os TRI�NGULOS.
    // Segundo, computamos as normais dos V�RTICES atrav�s do m�todo proposto
    // por Gourad, onde a normal de cada v�rtice vai ser a m�dia das normais de
    // todas as faces que compartilham este v�rtice.

    size_t num_vertices = this->attrib.vertices.size() / 3;

    std::vector<int> num_triangles_per_vertex(num_vertices, 0);
    std::vector<glm::vec4> vertex_normals(num_vertices, glm::vec4(0.0f,0.0f,0.0f,0.0f));

    for (size_t shape = 0; shape < this->shapes.size(); ++shape)
    {
        size_t num_triangles = this->shapes[shape].mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(this->shapes[shape].mesh.num_face_vertices[triangle] == 3);

            glm::vec4  vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = this->shapes[shape].mesh.indices[3*triangle + vertex];
                const float vx = this->attrib.vertices[3*idx.vertex_index + 0];
                const float vy = this->attrib.vertices[3*idx.vertex_index + 1];
                const float vz = this->attrib.vertices[3*idx.vertex_index + 2];
                vertices[vertex] = glm::vec4(vx,vy,vz,1.0);
            }

            const glm::vec4  a = vertices[0];
            const glm::vec4  b = vertices[1];
            const glm::vec4  c = vertices[2];

            // PREENCHA AQUI o c�lculo da normal de um tri�ngulo cujos v�rtices
            // est�o nos pontos "a", "b", e "c", definidos no sentido anti-hor�rio.
            const glm::vec4  n = crossproduct((a-b),(a-c));

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = this->shapes[shape].mesh.indices[3*triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] += n;
                this->shapes[shape].mesh.indices[3*triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    this->attrib.normals.resize( 3*num_vertices );

    for (size_t i = 0; i < vertex_normals.size(); ++i)
    {
        glm::vec4 n = vertex_normals[i] / (float)num_triangles_per_vertex[i];
        n /= norm(n);
        this->attrib.normals[3*i + 0] = n.x;
        this->attrib.normals[3*i + 1] = n.y;
        this->attrib.normals[3*i + 2] = n.z;
    }
}

// Constr�i tri�ngulos para futura renderiza��o a partir de um ObjModel.
void ObjModel::buildTriangles()
{
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    for (size_t shape = 0; shape < this->shapes.size(); ++shape)
    {
        size_t first_index = this->indices.size();
        size_t num_triangles = this->shapes[shape].mesh.num_face_vertices.size();

        const float minval = std::numeric_limits<float>::min();
        const float maxval = std::numeric_limits<float>::max();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(this->shapes[shape].mesh.num_face_vertices[triangle] == 3);

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = this->shapes[shape].mesh.indices[3*triangle + vertex];

                this->indices.push_back(first_index + 3*triangle + vertex);

                const float vx = this->attrib.vertices[3*idx.vertex_index + 0];
                const float vy = this->attrib.vertices[3*idx.vertex_index + 1];
                const float vz = this->attrib.vertices[3*idx.vertex_index + 2];
                //printf("tri %d vert %d = (%.2f, %.2f, %.2f)\n", (int)triangle, (int)vertex, vx, vy, vz);
                this->model_coefficients.push_back( vx ); // X
                this->model_coefficients.push_back( vy ); // Y
                this->model_coefficients.push_back( vz ); // Z
                this->model_coefficients.push_back( 1.0f ); // W

                if ( this->attrib.normals.size() >= (size_t)3*idx.normal_index )
                {
                    const float nx = this->attrib.normals[3*idx.normal_index + 0];
                    const float ny = this->attrib.normals[3*idx.normal_index + 1];
                    const float nz = this->attrib.normals[3*idx.normal_index + 2];
                    this->normal_coefficients.push_back( nx ); // X
                    this->normal_coefficients.push_back( ny ); // Y
                    this->normal_coefficients.push_back( nz ); // Z
                    this->normal_coefficients.push_back( 0.0f ); // W
                }

                if ( this->attrib.texcoords.size() >= (size_t)2*idx.texcoord_index )
                {
                    const float u = this->attrib.texcoords[2*idx.texcoord_index + 0];
                    const float v = this->attrib.texcoords[2*idx.texcoord_index + 1];
                    this->texture_coefficients.push_back( u );
                    this->texture_coefficients.push_back( v );
                }
            }
        }
    }
}

std::vector<float> ObjModel::getModelCoefficients()
{
    return this->model_coefficients;
}

std::vector<float> ObjModel::getNormalCoefficients()
{
    return this->normal_coefficients;
}

std::vector<float> ObjModel::getTextureCoefficients()
{
    return this->texture_coefficients;
}

std::vector<GLuint> ObjModel::getIndices()
{
    return this->indices;
}
