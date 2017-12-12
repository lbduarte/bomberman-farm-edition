#ifndef VIRTUALSCENE_H
#define VIRTUALSCENE_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "matrices.h"
#include "RawModel.h"
#include "Renderer.h"
#include "ObjModel.h"
#include "Loader.h"
#include "ObjectId.h"

namespace Graphics
{
    namespace VirtualScene
    {

            static RawModel plan(0, 0);
            static RawModel cube(0, 0);

            static std::vector<glm::mat4> wall_models;
            static glm::vec4 cubes_positions[11][11][2];

            void init(Loader loader);
            void drawObjects(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
            void drawPlans(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
            void drawWoodCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
    }
}

#endif // VIRTUALSCENE_H
