#include "RawModel.h"

using namespace Graphics;

RawModel::RawModel(GLuint vaoID, int vertexCount)
{
    m_VaoID = vaoID;
    m_VertexCount = vertexCount;
}

RawModel::~RawModel()
{

}

GLuint RawModel::getVaoID()
{
    return m_VaoID;
}

int RawModel::getVertexCount()
{
    return m_VertexCount;
}
