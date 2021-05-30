#ifndef __MODELTREE_H__
#define __MODELTREE_H__

#include "ModelStaticPoint.h"

class ModelTree : public ModelStaticPoint {
   private:
    /*póżniej jakiś typ zmiennej do odwołania do vertices, etc w GPU*/
   public:
    ModelTree(glm::vec2 pos, std::vector<float> *verts, std::vector<float> *colors);
    ~ModelTree(){};
};

#endif  // __MODELTREE_H__