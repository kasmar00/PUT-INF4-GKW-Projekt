#ifndef __ASSET_LOADER_H__
#define __ASSET_LOADER_H__

#include <string>
#include <utility>
#include <vector>

#include "Model.h"

class AssetLoader {
   private:
   public:
    AssetLoader();
    ~AssetLoader();

    std::pair<std::vector<float>, std::vector<float>> loadObj(std::string fileName);
};

#endif