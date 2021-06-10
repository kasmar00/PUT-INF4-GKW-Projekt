#ifndef __MODELDYNAMIC_H__
#define __MODELDYNAMIC_H__

#include <glm/glm.hpp>
#include <utility>
#include <vector>

#include "Model.h"

class ModelDynamic : public Model {
   private:
    float locationX;
    float locationY;
    float height;
    int direction;
    float rotation;

    unsigned long int mapIterator;
    float timer;

   public:
    std::vector<float> bodyVerts;
    std::vector<float> bodyColors;
    std::vector<float> wheelVerts;
    std::vector<float> wheelColors;
    std::vector<std::pair<float, float>> map;
    int bodyVertexCount, wheelVertexCount;

    ModelDynamic(glm::vec2 pos);
    ~ModelDynamic(){};
    void draw(glm::mat4 M);
    void drawWheel(glm::mat4 M);

    void setHeight(float height);
    void setDirection(int direction);
};

#endif  // __MODELDYNAMIC_H__