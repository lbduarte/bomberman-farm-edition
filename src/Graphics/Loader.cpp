#include "Loader.h"

using namespace Graphics;

Loader::Loader()
{

}

Loader::~Loader()
{

}

RawModel Loader::loadToVAO(std::vector<GLfloat> model_coefficients, std::vector<GLuint> indices, std::vector<GLfloat> color_coefficients)
{

    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(POSITION, 4, model_coefficients);
    storeDataInAttributeList(COLOR, 4, color_coefficients);
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
