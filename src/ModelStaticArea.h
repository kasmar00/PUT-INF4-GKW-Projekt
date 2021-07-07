#ifndef __MODELSTATICAREA_H__
#define __MODELSTATICAREA_H__

#include <vector>

#include "ModelStatic.h"

class ModelStaticArea : public ModelStatic {
   private:
    std::vector<glm::vec2> coords;
    std::vector<glm::vec4> verts;
    std::vector<glm::vec2> textureCoords;
    std::vector<glm::vec4> normals;

    float maxHeight;
    float minHeight;
    void createCoords();

   public:
    ModelStaticArea(std::vector<glm::vec2> coords, float minHeight, float maxheight);
    virtual ~ModelStaticArea(){};

    void draw(glm::mat4 M);
};

#endif  // __MODELSTATICAREA_H__