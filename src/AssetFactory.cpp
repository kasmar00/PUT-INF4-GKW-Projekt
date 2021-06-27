#include "AssetFactory.h"

#include "ModelStaticArea.h"
#include "ModelStaticPlanar.h"
#include "ModelStaticPoint.h"

void AssetFactory::createBuilding(struct object_data data) {
    // creates a bulding: walls, roof and floor

    ModelStaticArea* walls = new ModelStaticArea(data.coords);

    float maxheight = 4;
    float minheight = 0;
    if (data.props.contains("building:levels"))
        maxheight = std::stoi(data.props["building:levels"]) * 4;
    if (data.props.contains("building:min_level"))
        minheight = std::stoi(data.props["building:min_level"]) * 4;
    if (data.props["building"] == "roof" || data.props["building:part"] == "roof") {
        // building->addColor(glm::vec4(0.0f));

        // walls->addWalls();
    } else {
        walls->addWalls();
    }

    ModelStaticPlanar* roof = new ModelStaticPlanar(data.coords, maxheight);
    roof->createCoords();
    roof->addTexture(this->textures["building"]);
    this->models.push_back(roof);

    //TODO: remove floor from roofs, nie tyle co remove co przenieśc 20-30 cm poniżej dachu
    ModelStaticPlanar* floor = new ModelStaticPlanar(data.coords, minheight);
    floor->createCoords();
    floor->addTexture(this->textures["building"]);
    this->models.push_back(floor);

    walls->addTexture(this->textures["building"]);

    walls->addHeight(minheight, maxheight);
    walls->createCoords();
    this->models.push_back(walls);
}

void AssetFactory::createGrass(struct object_data data) {
    // creates grass
    auto* tmp = new ModelStaticPlanar(data.coords, 0.01f);
    // tmp->addHeight(0.01f, 0.01f);  //fix for z fighting
    tmp->addTexture(this->textures["grass"]);
    tmp->createCoords();
    this->models.push_back(tmp);
}

void AssetFactory::createArea(struct object_data data) {
    auto* tmp = new ModelStaticPlanar(data.coords, 0);
    // tmp->addHeight(0, 0);

    // auto color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    // if (i.props["area:highway"] == "footway")
    //     color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
    // else if (i.props["area:highway"] == "cycleway")
    //     color = glm::vec4(0.8f, 0.4f, 0.4f, 1.0f);
    //TODO: add more conditions?

    // tmp->addColor(color);
    tmp->addTexture(this->textures["area"]);
    tmp->createCoords();
    this->models.push_back(tmp);
}

void AssetFactory::createPoint(struct object_data data, std::string texture, std::vector<float>* verts, std::vector<float>* texCoords) {
    // creates a pointy object

    auto m = new ModelStaticPoint(data.coords.back(), verts, texCoords);
    if (data.props.contains("direction"))
        m->setDirection(std::stoi(data.props["direction"]));
    m->addTexture(this->textures[texture]);
    this->models.push_back(m);
}
