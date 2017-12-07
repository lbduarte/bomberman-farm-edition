#include "Loader.h"

using namespace Graphics;

Loader::Loader()
{

}

Loader::~Loader()
{

}

RawModel Loader::loadToVAO(GLfloat* positions)
{
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, positions);
    unbindVAO();
    // We divide by 4 because each vertex has 4 components (X, Y, Z, W)
    return RawModel(vaoID, (sizeof(positions)/sizeof(positions[0])/ 4));
}

void Loader::cleanUp()
{

}

GLuint Loader::createVAO()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, GLfloat* data)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, 4, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}
