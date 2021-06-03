#ifndef __MODELSTATICAREA_H__
#define __MODELSTATICAREA_H__

#include <vector>

#include "GL/glew.h"
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

    GLuint tex;
    std::vector<glm::vec2> textureCoords;

    void createCoordsPlanar(std::vector<glm::vec2> data);
    std::vector<std::vector<glm::vec2>> divideIntoConvex(std::vector<glm::vec2> coords, bool dir);

   public:
    ModelStaticArea(std::vector<glm::vec2> coords);
    virtual ~ModelStaticArea(){};

    void createCoords();
    void addHeight(float minHeight, float maxheight);
    void addWalls();
    void addColor(glm::vec4 col);
    void addTexture(GLuint texture);

    void draw(glm::mat4 M);
};

#endif  // __MODELSTATICAREA_H__