#include "AssetManager.h"

#include "ModelBench.h"
#include "ModelStaticArea.h"
#include "ModelTree.h"

AssetManager::AssetManager() {
    this->data_loader = DataLoader();
}

AssetManager::~AssetManager() {
}

void AssetManager::generate_models_from_path(std::string path) {
    //area data
    this->data_buildings = this->data_loader.load_planar_file(path + "/buildings");
    for (auto i : data_buildings) {
        float height = 4;
        bool walls = true;
        if (i.props.contains("building:levels"))
            height = std::stoi(i.props["building:levels"]) * 4;
        if (i.props["building"] == "roof")
            walls = false;

        this->models.push_back(new ModelStaticArea(i.coords, walls, height));
    }

    this->data_grass = this->data_loader.load_planar_file(path + "/grass");
    for (auto i : data_grass) {
        this->models.push_back(new ModelStaticArea(i.coords));
    }
    //TODO add other areas

    //pointy data
    this->data_trees = this->data_loader.load_point_file(path + "/trees");
    for (auto i : data_trees) {
        auto m = new ModelTree(i.coords.back());
        if (i.props.contains("height"))
            m->setHeight(std::stoi(i.props["height"]));
        this->models.push_back(m);
    }
    this->data_benches = this->data_loader.load_point_file(path + "/benches");
    for (auto i : data_benches) {
        auto m = new ModelBench(i.coords.back());
        if (i.props.contains("direction"))
            m->setDirection(std::stoi(i.props["direction"]));
        this->models.push_back(m);
    }
    //TODO add lights

    //This asserts length of every load
    this->sanity_check_load();
}

void AssetManager::sanity_check_load() {
    printf("Loaded %ld buildings\n", data_buildings.size());  //not an assert, because there may be no ex. grass in the area
    printf("Loaded %ld grass\n", data_grass.size());
    printf("Loaded %ld trees\n", data_trees.size());
    printf("Loaded %ld benches\n", data_benches.size());
    for (auto i : data_buildings) {
        assert(i.coords.size() > 0);  //sprawdzenie czy obiekt zawiera koordynaty
        assert(i.props.size() > 0);   //sprawdzenie czy obiekt zawiera tagi
    }
    //TODO: Add model checks once loaded
}