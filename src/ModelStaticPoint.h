#ifndef __MODELSTATICPOINT_H__
#define __MODELSTATICPOINT_H__

#include <vector>

#include "GL/glew.h"
#include "ModelStatic.h"

class ModelStaticPoint : public ModelStatic {
   private:
    float locationX;
    float locationY;
    float height;
    int direction;
    GLuint tex;

   public:
    std::vector<float> verts;
    std::vector<float> texCoords;
    int vertexCount;

    ModelStaticPoint(glm::vec2 pos);
    virtual ~ModelStaticPoint(){};
    void draw(glm::mat4 M);

    void setHeight(float height);
    void setDirection(int direction);
    void addTexture(GLuint texture);
};

#endif  // __MODELSTATICPOINT_H__