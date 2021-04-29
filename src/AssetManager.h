#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <vector>

#include "AssetLoader.h"
#include "DataLoader.h"
#include "Model.h"

class AssetManager {
   private:
    std::vector<Model*> models;
    std::vector<object_data> data;
    AssetLoader ass_loader;
    DataLoader data_loader;

   public:
    AssetManager();
    ~AssetManager();
    void sanity_check_load();
    void generate_models_from_file(std::string filename);
};

#endif