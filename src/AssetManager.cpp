#include "AssetManager.h"

AssetManager::AssetManager() {
    this->data_loader = DataLoader();
}

AssetManager::~AssetManager() {
}

void AssetManager::generate_models_from_file(std::string filename) {
    this->data = this->data_loader.load_file(filename);

    //This asserts length of every load
    this->sanity_check_load();
}

void AssetManager::sanity_check_load() {
    for (auto i : data) {
        assert(i.coords.size() > 0);

        //TODO: Uncomment once
        // https://github.com/kasmar00/PUT-INF4-GKW-Projekt/issues/4
        //is resolved

        //assert(i.props.size() > 0);
    }
    //TODO: Add model checks once loaded
}