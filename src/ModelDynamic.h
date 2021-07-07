#ifndef __MODELDYNAMIC_H__
#define __MODELDYNAMIC_H__

#include <GL/glew.h>

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
    std::vector<float>* verts;
    std::vector<float>* texCoords;
    std::vector<float>* normals;
    int vertexCount;
    GLuint tex;

    std::vector<std::pair<float, float>> map;
    int bodyVertexCount, wheelVertexCount;

    ModelDynamic(glm::vec2 pos, GLuint texture, std::vector<float>* verts, std::vector<float>* texCoords, std::vector<float>* normals);
    ~ModelDynamic(){};
    void draw(glm::mat4 M);

    void setHeight(float height);
    void setDirection(int direction);
};

#endif  // __MODELDYNAMIC_H__