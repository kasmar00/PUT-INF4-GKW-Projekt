#ifndef __ASSETFACTORY_H__
#define __ASSETFACTORY_H__

#include <vector>

// #include "AssetLoader.h"
#include "DataLoader.h"
#include "ModelStatic.h"

class AssetFactory {
   private:
    std::vector<ModelStatic*> models;
    std::unordered_map<std::string, GLuint> textures;
    // std::unordered_map<std::string, asl::mesh> meshes;

   public:
    std::vector<ModelStatic*> getModels() {
        return this->models;
    };
    void addTexture(std::string name, GLuint texture) {
        this->textures[name] = texture;
    };
    // void addMesh(std::string name, asl::mesh mesh) {
    //     this->meshes[name] = mesh;
    // }

    void createBuilding(struct object_data data);
    void createGrass(struct object_data data);
    void createArea(struct object_data data);
    void createPoint(struct object_data data, std::string texture, std::vector<float>* verts, std::vector<float>* texCoords);
};

#endif  // __ASSETFACTORY_H__