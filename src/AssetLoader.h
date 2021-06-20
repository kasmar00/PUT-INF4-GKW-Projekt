#ifndef __ASSET_LOADER_H__
#define __ASSET_LOADER_H__

#include <string>
#include <utility>
#include <vector>

#include "Model.h"

namespace asl {
typedef std::vector<std::vector<float>> mesh;
typedef std::vector<mesh> model;
enum : int  // mesh indexes
{
    v,
    vt,
    vn
};
}  // namespace asl

class AssetLoader {
   private:
   public:
    AssetLoader();
    ~AssetLoader();

    asl::model loadObj(std::string fileName);
};

#endif