#ifndef __MODELSTATICPOINT_H__
#define __MODELSTATICPOINT_H__

#include <vector>

#include "ModelStatic.h"

class ModelStaticPoint : public ModelStatic {
   private:
   public:
    float locationX;
    float locationY;
    float height;
    float direction;

    std::vector<float> verts;
    std::vector<float> colors;
    int vertexCount;
    ModelStaticPoint(){};
    virtual ~ModelStaticPoint(){};
    void draw(glm::mat4 M);
};

#endif  // __MODELSTATICPOINT_H__