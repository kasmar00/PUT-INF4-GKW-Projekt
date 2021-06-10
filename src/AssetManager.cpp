#include "AssetManager.h"

#include "ModelBench.h"
#include "ModelStaticArea.h"
#include "ModelTree.h"

AssetManager::AssetManager() {
    this->data_loader = DataLoader();
    this->ass_loader = AssetLoader();
}

AssetManager::~AssetManager() {
}

void AssetManager::generate_models_from_path(std::string path) {
    //area data
    this->data_buildings = this->data_loader.load_planar_file(path + "/buildings");
    for (auto i : data_buildings) {
        ModelStaticArea* tmp = new ModelStaticArea(i.coords);

        float maxheight = 4;
        float minheight = 0;
        if (i.props.contains("building:levels"))
            maxheight = std::stoi(i.props["building:levels"]) * 4;
        if (i.props.contains("building:min_level"))
            minheight = std::stoi(i.props["building:min_level"]) * 4;
        if (i.props["building"] == "roof" || i.props["building:part"] == "roof") {
            tmp->addColor(glm::vec4(0.0f));
        } else {
            tmp->addWalls();
        }
        tmp->addHeight(minheight, maxheight);
        tmp->createCoords();
        this->models.push_back(tmp);
    }

    this->data_grass = this->data_loader.load_planar_file(path + "/grass");
    for (auto i : data_grass) {
        auto* tmp = new ModelStaticArea(i.coords);
        tmp->addColor(glm::vec4(0.8f, 1.0f, 0.0f, 1.0f));
        tmp->addHeight(0.1f, 0.1f);  //fix for x fighting
        tmp->createCoords();
        this->models.push_back(tmp);
    }

    this->data_areas = this->data_loader.load_planar_file(path + "/areas");
    for (auto i : data_areas) {
        auto* tmp = new ModelStaticArea(i.coords);
        tmp->addHeight(0, 0);

        auto color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        if (i.props["area:highway"] == "footway")
            color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
        else if (i.props["area:highway"] == "cycleway")
            color = glm::vec4(0.8f, 0.4f, 0.4f, 1.0f);
        //TODO: add more conditions?

        tmp->addColor(color);
        tmp->createCoords();
        this->models.push_back(tmp);
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
        auto m = new ModelTree(i.coords.back(), treeVerts, treeColors);
        if (i.props.contains("height"))
            m->setHeight(std::stoi(i.props["height"]));
        this->models.push_back(m);
    }
    this->data_benches = this->data_loader.load_point_file(path + "/benches");
    for (auto i : data_benches) {
        //TODO: tymczasowo przeniesione na modelStaticPoint, w przyszłości rozważyć sens istnienia ModelBench i ModelTree
        auto m = new ModelStaticPoint(i.coords.back(), benchVerts, benchColors);
        // auto m = new ModelBench(i.coords.back());
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
    printf("Loaded %ld areas\n", data_areas.size());
    printf("Loaded %ld trees\n", data_trees.size());
    printf("Loaded %ld benches\n", data_benches.size());
    for (auto i : data_buildings) {
        assert(i.coords.size() > 0);  //sprawdzenie czy obiekt zawiera koordynaty
        assert(i.props.size() > 0);   //sprawdzenie czy obiekt zawiera tagi
    }
    //TODO: Add model checks once loaded
}