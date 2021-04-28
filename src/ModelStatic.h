#ifndef __MODELSTATIC_H__
#define __MODELSTATIC_H__

#include <glm/glm.hpp>

#include "Model.h"

class ModelStatic : public Model {
   private:
   public:
    ModelStatic(){};
    virtual ~ModelStatic(){};
    virtual void draw(glm::mat4 M) = 0;
};

#endif  // __MODELSTATIC_H__