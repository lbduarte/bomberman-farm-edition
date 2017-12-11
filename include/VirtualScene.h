#ifndef VIRTUALSCENE_H
#define VIRTUALSCENE_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrices.h"
#include "RawModel.h"
#include "Renderer.h"

namespace Graphics
{
    namespace VirtualScene
    {

            static RawModel plan(0, 0);
            static RawModel cube(0, 0);

            void init();
            void drawObjects(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
    }
}

#endif // VIRTUALSCENE_H
