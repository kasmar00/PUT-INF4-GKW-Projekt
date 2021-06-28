#ifndef __MODELSTATICPLANAR_H__
#define __MODELSTATICPLANAR_H__

#include <vector>

#include "ModelStatic.h"

class ModelStaticPlanar : public ModelStatic {
   private:
    std::vector<glm::vec2> coords;
    std::vector<glm::vec4> verts;
    std::vector<glm::vec2> textureCoords;
    std::vector<glm::vec4> normals;

    bool dir;
    float height;

    void createCoords();
    void createCoordsPlanar(std::vector<glm::vec2> data);
    std::vector<std::vector<glm::vec2>> divideIntoConvex(std::vector<glm::vec2> coords, bool dir);

   public:
    ModelStaticPlanar(std::vector<glm::vec2> data, float height, bool dir);
    ModelStaticPlanar(std::vector<glm::vec2> data, float height);
    ~ModelStaticPlanar();

    void draw(glm::mat4 M);
};

#endif  // __MODELSTATICPLANAR_H__