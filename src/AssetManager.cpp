#include "AssetManager.h"

#include "AssetFactory.h"
#include "ModelStaticArea.h"
#include "ModelStaticPlanar.h"
#include "ModelStaticPoint.h"
#include "SkyBox.h"

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
    factory.addTexture("roof", this->ass_loader.loadTexture("textures/roof.png"));
    for (auto i : data_buildings) {
        factory.createBuilding(i);
    }

    this->data_grass = this->data_loader.load_planar_file(path + "/grass");
    factory.addTexture("grass", this->ass_loader.loadTexture("textures/grass.png"));
    for (auto i : data_grass) {
        factory.createGrass(i);
    }

    this->data_areas = this->data_loader.load_planar_file(path + "/areas");
    factory.addTexture("area", this->ass_loader.loadTexture("textures/metal.png"));
    for (auto i : data_areas) {
        factory.createArea(i);
    }

    auto tmp = this->data_loader.load_planar_file(path + "/dump");
    factory.addTexture("dirt", this->ass_loader.loadTexture("textures/dirt.png"));
    for (auto i : tmp) {
        factory.createDirt(i);
    }

    //OBJ loading
    //TODO: because there's no better place
    auto tree_all = this->ass_loader.loadObj("models/smalltree.obj");
    auto treeObj = tree_all[0];
    auto coronaObj = tree_all[1];
    auto benchObj = this->ass_loader.loadObj("models/bench_tri.obj")[0];
    auto lampObj_all = this->ass_loader.loadObj("models/bylamp.obj");
    auto lampObj = lampObj_all[0];
    auto kloszObj = lampObj_all[1];

    //bez tego \/\/ jest  segfault a mi za mało płacą żeby go naprawiać efektywniej ¯\_(ツ)_/¯
    std::vector<float>* treeVerts = new std::vector<float>(treeObj[asl::v]);
    std::vector<float>* treeTexture = new std::vector<float>(treeObj[asl::vt]);  //if everything loaded-change to texture
    std::vector<float>* treeNormals = new std::vector<float>(treeObj[asl::vn]);
    std::vector<float>* coronaVerts = new std::vector<float>(coronaObj[asl::v]);
    std::vector<float>* coronaTexture = new std::vector<float>(coronaObj[asl::vt]);  //if everything loaded-change to texture
    std::vector<float>* coronaNormals = new std::vector<float>(coronaObj[asl::vn]);
    std::vector<float>* benchVerts = new std::vector<float>(benchObj[asl::v]);
    std::vector<float>* benchTexture = new std::vector<float>(benchObj[asl::vt]);
    std::vector<float>* benchNormals = new std::vector<float>(benchObj[asl::vn]);
    std::vector<float>* lampVerts = new std::vector<float>(lampObj[asl::v]);
    std::vector<float>* lampTexture = new std::vector<float>(lampObj[asl::vt]);
    std::vector<float>* lampNormals = new std::vector<float>(lampObj[asl::vn]);
    std::vector<float>* kloszVerts = new std::vector<float>(kloszObj[asl::v]);
    std::vector<float>* kloszTexture = new std::vector<float>(kloszObj[asl::vt]);
    std::vector<float>* kloszNormals = new std::vector<float>(kloszObj[asl::vn]);

    //pointy data
    factory.addTexture("bench", this->ass_loader.loadTexture("textures/bench.png"));

    this->data_trees = this->data_loader.load_point_file(path + "/trees");
    for (auto i : data_trees) {
        factory.createPoint(i, "bench", treeVerts, treeTexture, treeNormals);
        factory.createPoint(i, "grass", coronaVerts, coronaTexture, coronaNormals);
    }
    this->data_benches = this->data_loader.load_point_file(path + "/benches");
    for (auto i : data_benches) {
        factory.createPoint(i, "bench", benchVerts, benchTexture, benchNormals);
    }

    this->data_lamps = this->data_loader.load_point_file(path + "/lights");
    factory.addTexture("light", this->ass_loader.loadTexture("textures/light.png"));
    for (auto i : data_lamps) {
        factory.createPoint(i, "area", lampVerts, lampTexture, lampNormals);
        factory.createPoint(i, "light", kloszVerts, kloszTexture, kloszNormals);
    }

    this->models = factory.getModels();

    SkyBox::GetIntstance()->addTexture(ass_loader.loadTexture("textures/skybox.png"));

    //This asserts length of every load
    this->sanity_check_load();
}

std::vector<glm::vec4> AssetManager::getLamps() {
    std::vector<glm::vec4> tmp;
    for (auto i : this->data_lamps)
        tmp.push_back(glm::vec4(i.coords.back().x, 6.6, i.coords.back().y, 1));
    return tmp;
}

void AssetManager::sanity_check_load() {
    printf("Loaded %ld buildings\n", data_buildings.size());  //not an assert, because there may be no ex. grass in the area
    printf("Loaded %ld grass\n", data_grass.size());
    printf("Loaded %ld areas\n", data_areas.size());
    printf("Loaded %ld trees\n", data_trees.size());
    printf("Loaded %ld benches\n", data_benches.size());
    printf("Loaded %ld lamps\n", data_lamps.size());
    for (auto i : data_buildings) {
        assert(i.coords.size() > 0);  //sprawdzenie czy obiekt zawiera koordynaty
        assert(i.props.size() > 0);   //sprawdzenie czy obiekt zawiera tagi
    }
    //TODO: Add model checks once loaded
}