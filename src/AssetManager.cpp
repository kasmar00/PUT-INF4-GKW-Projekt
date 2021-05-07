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
    printf("Loaded %ld elements\n", data.size());  //not an assert, because there may be no ex. grass in the area
    for (auto i : data) {
        assert(i.coords.size() > 0);  //sprawdzenie czy obiekt zawiera koordynaty
        assert(i.props.size() > 0);   //sprawdzenie czy obiekt zawiera tagi
    }
    //TODO: Add model checks once loaded
}