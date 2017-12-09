#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics
{
    class RawModel
    {
    private:
        GLuint m_VaoID;
        int m_VertexCount;
    public:
        RawModel(GLuint vaoID, int vertexCount);
        ~RawModel();
        GLuint getVaoID();
        int getVertexCount();

    private:
    };
}

#endif // RAWMODEL_H
