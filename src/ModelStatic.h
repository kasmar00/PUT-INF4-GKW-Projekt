#ifndef __MODELSTATIC_H__
#define __MODELSTATIC_H__

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Model.h"

class ModelStatic : public Model {
   protected:
    GLuint tex;
    glm::vec4 color = glm::vec4(1);

   public:
    ModelStatic(){};
    virtual ~ModelStatic(){};
    virtual void draw(glm::mat4 M) = 0;

    void addTexture(GLuint texture);
    void setColor(glm::vec4 col);
};

#endif  // __MODELSTATIC_H__