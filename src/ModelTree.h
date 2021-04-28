#ifndef __MODELTREE_H__
#define __MODELTREE_H__

#include "ModelStaticPoint.h"

class ModelTree : public ModelStaticPoint {
   private:
    /*póżniej jakiś typ zmiennej do odwołania do vertices, etc w GPU*/
   public:
    ModelTree();
    ~ModelTree(){};
};

#endif  // __MODELTREE_H__