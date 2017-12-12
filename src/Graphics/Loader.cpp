#include "Loader.h"


using namespace Graphics;

Loader::Loader()
{
    this->g_NumLoadedTextures = 0;

}

Loader::~Loader()
{

}

RawModel Loader::loadToVAO(std::vector<GLfloat> model_coefficients, std::vector<GLuint> indices)
{
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(POSITION, 4, model_coefficients);
    unbindVAO();
    RawModel model(vaoID, indices.size());
    return model;
}

RawModel Loader::loadObjToVAO(ObjModel object)
{
    GLuint vaoID = createVAO();
    storeDataInAttributeList(POSITION, 4, object.getModelCoefficients());
    if ( !object.getNormalCoefficients().empty() )
        storeDataInAttributeList(NORMAL, 4, object.getNormalCoefficients());
    if ( !object.getTextureCoefficients().empty() )
        storeDataInAttributeList(TEXTURE, 2, object.getTextureCoefficients());
    bindIndicesBuffer(object.getIndices());
    unbindVAO();
    RawModel model(vaoID, object.getIndices().size());
    return model;
}

void Loader::cleanUp()
{
    for(unsigned int i=0; i < vaos.size(); i++)
    {
        glDeleteVertexArrays(1, &vaos.at(i));
    }

    for(unsigned int i=0; i < vbos.size(); i++)
    {
        glDeleteBuffers(1, &vbos.at(i));
    }
}

GLuint Loader::createVAO()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(AttributeLocation location, int number_of_dimensions, std::vector<GLfloat> data)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GL_FLOAT), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(GL_FLOAT), &data.at(0));
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<GLuint> data)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GL_UNSIGNED_INT), &data.at(0), GL_STATIC_DRAW);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

// Função que carrega uma imagem para ser utilizada como textura
void Loader::loadTextureImage(const char* filename)
{
    printf("Carregando imagem \"%s\"... ", filename);

    // Primeiro fazemos a leitura da imagem do disco
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);

    if ( data == NULL )
    {
        fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }

    printf("OK (%dx%d).\n", width, height);

    // Agora criamos objetos na GPU com OpenGL para armazenar a textura
    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    // Veja slide 160 do documento "Aula_20_e_21_Mapeamento_de_Texturas.pdf"
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Parâmetros de amostragem da textura. Falaremos sobre eles em uma próxima aula.
    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Agora enviamos a imagem lida do disco para a GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    GLuint textureunit = this->g_NumLoadedTextures;
    glActiveTexture(GL_TEXTURE0 + textureunit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(textureunit, sampler_id);

    stbi_image_free(data);

    this->g_NumLoadedTextures += 1;
}

int Loader::getNumTextures()
{
    return this->g_NumLoadedTextures;
}
