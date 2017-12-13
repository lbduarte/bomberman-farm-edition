#ifndef VIRTUALSCENE_H
#define VIRTUALSCENE_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <time.h>
#include "matrices.h"
#include "RawModel.h"
#include "Renderer.h"
#include "ObjModel.h"
#include "Loader.h"
#include "ObjectId.h"
#include "Keyboard.h"

#define NUM_CUBES 55
namespace Graphics
{
    namespace VirtualScene
    {

            static RawModel plan(0, 0);
            static RawModel cube(0, 0);
            static RawModel cow(0, 0);
            static RawModel bomb(0, 0);

            static glm::vec4 wall_positions[4][2];
            static glm::vec4 cubes_positions[11][11][2];

            static int num_cubes = NUM_CUBES;
            static int random_positions[NUM_CUBES][2];
            static int cow_position[2];
            static float cow_angleY;

            void init(Loader loader);
            void drawObjects(GLint model_uniform, GLint object_id_uniform, Renderer renderer, bool drawCow);
            void drawPlans(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
            void drawWoodCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
            void drawHayCubes(GLint model_uniform, GLint object_id_uniform, Renderer renderer);
    }
}

#endif // VIRTUALSCENE_H
