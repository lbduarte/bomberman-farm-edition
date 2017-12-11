#include "VirtualScene.h"


using namespace Graphics;

VirtualScene::VirtualScene()
{

    Graphics::ObjModel obj("../../data/plane.obj");
    obj.computeNormals();
    obj.buildTriangles();
    Graphics::RawModel model = loader.loadObjToVAO(obj);
    glUniform1i(object_id_uniform, PLAN);
}

