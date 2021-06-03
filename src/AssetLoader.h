#ifndef __ASSET_LOADER_H__
#define __ASSET_LOADER_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "Model.h"

// dodać makra na hashmapę z danymi
extern GLuint texGlobal;

class AssetLoader {
   private:
    std::vector<GLuint> allTextures;

   public:
    AssetLoader();
    ~AssetLoader();

    GLuint loadTexture(std::string filename);
};

#endif