#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <vector>

#include "AssetLoader.h"
#include "DataLoader.h"
#include "ModelStatic.h"

class AssetManager {
   private:
    //area data
    std::vector<object_data> data_buildings;
    std::vector<object_data> data_grass;
    std::vector<object_data> data_areas;
    //pointy data
    std::vector<object_data> data_trees;
    std::vector<object_data> data_benches;

    AssetLoader ass_loader;
    DataLoader data_loader;

   public:
    std::vector<ModelStatic*> models;
    AssetManager();
    ~AssetManager();
    void sanity_check_load();
    void generate_models_from_path(std::string path);
};

#endif