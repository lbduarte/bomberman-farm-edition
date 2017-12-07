#include "RawModel.h"

using namespace Graphics;

RawModel::RawModel(int vaoID, int vertexCount)
{
    m_VaoID = vaoID;
    m_VertexCount = vertexCount;
}

RawModel::~RawModel()
{

}

int RawModel::getVaoID()
{
    return m_VaoID;
}

int RawModel::getVertexCount()
{
    return m_VertexCount;
}
