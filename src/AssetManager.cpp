#include "AssetManager.h"

#include "AssetFactory.h"
#include "ModelStaticArea.h"
#include "ModelStaticPlanar.h"
#include "ModelStaticPoint.h"

AssetManager::AssetManager() {
    printf("Constructed asset manager!\n");
}

AssetManager::~AssetManager() {
    printf("deleting asset manager!\n");
}

void AssetManager::generate_models_from_path(std::string path) {
    //area data
    AssetFactory factory;

    this->data_buildings = this->data_loader.load_planar_file(path + "/buildings");
    factory.addTexture("building", this->ass_loader.loadTexture("textures/bricks.png"));
    for (auto i : data_buildings) {
        factory.createBuilding(i);
    }

    this->data_grass = this->data_loader.load_planar_file(path + "/grass");
    factory.addTexture("grass", this->ass_loader.loadTexture("textures/Grass.png"));
    for (auto i : data_grass) {
        factory.createGrass(i);
    }

    this->data_areas = this->data_loader.load_planar_file(path + "/areas");
    factory.addTexture("area", this->ass_loader.loadTexture("textures/metal.png"));
    for (auto i : data_areas) {
        factory.createArea(i);
    }

    //OBJ loading
    //TODO: because there's no better place
    auto treeObj = this->ass_loader.loadObj("models/suzanne_tri.obj")[0];
    auto benchObj = this->ass_loader.loadObj("models/bench_tri.obj")[0];

    //bez tego \/\/ jest  segfault a mi za mało płacą żeby go naprawiać efektywniej ¯\_(ツ)_/¯
    std::vector<float>* treeVerts = new std::vector<float>(treeObj[asl::v]);
    std::vector<float>* treeColors = new std::vector<float>(treeObj[asl::vt]);  //if everything loaded-change to texture
    std::vector<float>* benchVerts = new std::vector<float>(benchObj[asl::v]);
    std::vector<float>* benchColors = new std::vector<float>(benchObj[asl::vt]);

    //pointy data
    this->data_trees = this->data_loader.load_point_file(path + "/trees");
    for (auto i : data_trees) {
        factory.createPoint(i, "building", treeVerts, treeColors);
    }
    this->data_benches = this->data_loader.load_point_file(path + "/benches");
    for (auto i : data_benches) {
        factory.createPoint(i, "building", benchVerts, benchColors);
    }
    //TODO add lights

    this->models = factory.getModels();

    //This asserts length of every load
    this->sanity_check_load();
}

void AssetManager::sanity_check_load() {
    printf("Loaded %ld buildings\n", data_buildings.size());  //not an assert, because there may be no ex. grass in the area
    printf("Loaded %ld grass\n", data_grass.size());
    printf("Loaded %ld areas\n", data_areas.size());
    printf("Loaded %ld trees\n", data_trees.size());
    printf("Loaded %ld benches\n", data_benches.size());
    for (auto i : data_buildings) {
        assert(i.coords.size() > 0);  //sprawdzenie czy obiekt zawiera koordynaty
        assert(i.props.size() > 0);   //sprawdzenie czy obiekt zawiera tagi
    }
    //TODO: Add model checks once loaded
}