#include "AssetFactory.h"

#include "ModelDynamic.h"
#include "ModelStaticArea.h"
#include "ModelStaticPlanar.h"
#include "ModelStaticPoint.h"

void AssetFactory::createBuilding(struct object_data data) {
    // creates a bulding: walls, roof and floor

    float maxheight = 4;
    float minheight = 0;
    if (data.props.contains("building:levels"))
        maxheight = std::stoi(data.props["building:levels"]) * 4;
    if (data.props.contains("building:min_level"))
        minheight = std::stoi(data.props["building:min_level"]) * 4;
    if (data.props["building"] == "roof" || data.props["building:part"] == "roof") {
        minheight = maxheight - 0.4f;
    }

    ModelStaticArea* walls = new ModelStaticArea(data.coords, minheight, maxheight);

    ModelStaticPlanar* roof = new ModelStaticPlanar(data.coords, maxheight);
    roof->addTexture(this->textures["roof"]);
    this->models.push_back(roof);

    ModelStaticPlanar* floor = new ModelStaticPlanar(data.coords, minheight);
    floor->addTexture(this->textures["building"]);
    this->models.push_back(floor);

    walls->addTexture(this->textures["building"]);

    this->models.push_back(walls);
}

void AssetFactory::createGrass(struct object_data data) {
    // creates grass
    auto* tmp = new ModelStaticPlanar(data.coords, 0.01f);
    tmp->addTexture(this->textures["grass"]);
    this->models.push_back(tmp);

    //grass needs walls becouse of corretion for Z fighting
    auto* walls = new ModelStaticArea(data.coords, 0, 0.01f);
    walls->addTexture(this->textures["grass"]);
    this->models.push_back(walls);
}

void AssetFactory::createArea(struct object_data data) {
    auto* tmp = new ModelStaticPlanar(data.coords, 0);

    // auto color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    if (data.props["area:highway"] == "footway")
        tmp->setColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
    else if (data.props["area:highway"] == "cycleway")
        tmp->setColor(glm::vec4(0.8f, 0.4f, 0.4f, 1.0f));
    //TODO: add more conditions?

    // tmp->addColor(color);
    tmp->addTexture(this->textures["area"]);
    this->models.push_back(tmp);
}

void AssetFactory::createPoint(struct object_data data, std::string texture, std::vector<float>* verts, std::vector<float>* texCoords, std::vector<float>* normals) {
    // creates a pointy object

    auto m = new ModelStaticPoint(data.coords.back(), verts, texCoords, normals);
    if (data.props.contains("direction"))
        m->setDirection(std::stoi(data.props["direction"]));
    m->addTexture(this->textures[texture]);
    this->models.push_back(m);
}

void AssetFactory::createDirt(struct object_data data) {
    // creates grass
    auto* tmp = new ModelStaticPlanar(data.coords, -0.1f);
    tmp->addTexture(this->textures["dirt"]);
    this->models.push_back(tmp);
}

void AssetFactory::createDynamic(std::string texture, std::vector<float>* verts, std::vector<float>* texCoords, std::vector<float>* normals) {
    auto* tmp = new ModelDynamic(glm::vec2(-140, -50), this->textures[texture], verts, texCoords, normals);
    this->modelDyn.push_back(tmp);
}
