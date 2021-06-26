#include "AssetManager.h"

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
    this->data_buildings = this->data_loader.load_planar_file(path + "/buildings");
    GLuint textureBuilding = this->ass_loader.loadTexture("textures/bricks.png");
    for (auto i : data_buildings) {
        ModelStaticArea* building = new ModelStaticArea(i.coords);

        float maxheight = 4;
        float minheight = 0;
        if (i.props.contains("building:levels"))
            maxheight = std::stoi(i.props["building:levels"]) * 4;
        if (i.props.contains("building:min_level"))
            minheight = std::stoi(i.props["building:min_level"]) * 4;
        if (i.props["building"] == "roof" || i.props["building:part"] == "roof") {
            // building->addColor(glm::vec4(0.0f));
        } else {
            building->addWalls();
        }

        ModelStaticPlanar* roof = new ModelStaticPlanar(i.coords, maxheight);
        roof->createCoords();
        roof->addTexture(textureBuilding);
        this->models.push_back(roof);

        building->addTexture(textureBuilding);

        building->addHeight(minheight, maxheight);
        building->createCoords();
        this->models.push_back(building);
    }

    this->data_grass = this->data_loader.load_planar_file(path + "/grass");
    GLuint textureGrass = this->ass_loader.loadTexture("textures/Grass.png");
    for (auto i : data_grass) {
        auto* tmp = new ModelStaticPlanar(i.coords, 0.01f);
        // tmp->addHeight(0.01f, 0.01f);  //fix for z fighting
        tmp->addTexture(textureGrass);
        tmp->createCoords();
        this->models.push_back(tmp);
    }

    this->data_areas = this->data_loader.load_planar_file(path + "/areas");
    GLuint textureArea = this->ass_loader.loadTexture("textures/metal.png");
    for (auto i : data_areas) {
        auto* tmp = new ModelStaticPlanar(i.coords, 0);
        // tmp->addHeight(0, 0);

        // auto color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        // if (i.props["area:highway"] == "footway")
        //     color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
        // else if (i.props["area:highway"] == "cycleway")
        //     color = glm::vec4(0.8f, 0.4f, 0.4f, 1.0f);
        //TODO: add more conditions?

        // tmp->addColor(color);
        tmp->addTexture(textureArea);
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
        auto m = new ModelStaticPoint(i.coords.back(), treeVerts, treeColors);
        if (i.props.contains("height"))
            m->setHeight(std::stoi(i.props["height"]));
        m->addTexture(textureBuilding);
        this->models.push_back(m);
    }
    this->data_benches = this->data_loader.load_point_file(path + "/benches");
    for (auto i : data_benches) {
        auto m = new ModelStaticPoint(i.coords.back(), benchVerts, benchColors);
        if (i.props.contains("direction"))
            m->setDirection(std::stoi(i.props["direction"]));
        m->addTexture(textureBuilding);
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