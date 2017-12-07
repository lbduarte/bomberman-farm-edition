#ifndef RAWMODEL_H
#define RAWMODEL_H

namespace Graphics
{


    class RawModel
    {
    private:
        int m_VaoID;
        int m_VertexCount;
    public:
        RawModel(int vaoID, int vertexCount);
        ~RawModel();
        int getVaoID();
        int getVertexCount();

    private:
    };
}

#endif // RAWMODEL_H
