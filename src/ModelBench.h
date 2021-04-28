#ifndef __MODELBENCH_H__
#define __MODELBENCH_H__

#include "ModelStaticPoint.h"

class ModelBench : public ModelStaticPoint {
   private:
    /*jakiś typ zmiennej do odwołania do vertices, etc w GPU*/
   public:
    ModelBench();
    ~ModelBench(){};
};

#endif  // __MODELBENCH_H__