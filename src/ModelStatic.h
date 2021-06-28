#ifndef __MODELSTATIC_H__
#define __MODELSTATIC_H__

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Model.h"

class ModelStatic : public Model {
   protected:
    GLuint tex;

   public:
    ModelStatic(){};
    virtual ~ModelStatic(){};
    virtual void draw(glm::mat4 M) = 0;

    void addTexture(GLuint texture);
};

#endif  // __MODELSTATIC_H__