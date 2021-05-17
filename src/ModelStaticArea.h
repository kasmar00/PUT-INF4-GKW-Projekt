#ifndef __MODELSTATICAREA_H__
#define __MODELSTATICAREA_H__

#include <vector>

#include "ModelStatic.h"

class ModelStaticArea : public ModelStatic {
   private:
    std::vector<glm::vec2> coords;
    std::vector<glm::vec4> drawCoords;
    std::vector<glm::vec4> colors;

    float maxHeight;
    float minHeight;
    bool walls;
    glm::vec4 color;

   public:
    ModelStaticArea(std::vector<glm::vec2> coords);
    virtual ~ModelStaticArea(){};

    void createCoords();
    void addHeight(float minHeight, float maxheight);
    void addWalls();
    void addColor(glm::vec4 col);

    void draw(glm::mat4 M);
};

#endif  // __MODELSTATICAREA_H__