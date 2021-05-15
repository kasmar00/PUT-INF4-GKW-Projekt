#ifndef __MODELSTATICAREA_H__
#define __MODELSTATICAREA_H__

#include <vector>

#include "ModelStatic.h"

class ModelStaticArea : public ModelStatic {
   private:
    std::vector<glm::vec2> coords;
    std::vector<glm::vec4> drawCoords;
    std::vector<glm::vec4> colors;

    float height;

   public:
    ModelStaticArea(std::vector<glm::vec2> coords, bool walls = false, float height = 0.0f);
    virtual ~ModelStaticArea(){};

    void draw(glm::mat4 M);
};

#endif  // __MODELSTATICAREA_H__