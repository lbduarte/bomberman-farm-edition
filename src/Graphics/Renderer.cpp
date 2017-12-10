#include "Renderer.h"

using namespace Graphics;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
}

void Renderer::render(RawModel model)
{
    glBindVertexArray(model.getVaoID());
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
