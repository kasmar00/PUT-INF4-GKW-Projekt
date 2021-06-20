#ifndef __ASSET_LOADER_H__
#define __ASSET_LOADER_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <utility>
#include <vector>

#include "Model.h"

extern GLuint texGlobal;

namespace asl {
typedef std::vector<std::vector<float>> mesh;
typedef std::vector<mesh> model;
enum : int  // mesh indexes
{
    v,
    vt,
    vn
};
}  // namespace asl

class AssetLoader {
   private:
    std::vector<GLuint> allTextures;

   public:
    AssetLoader();
    ~AssetLoader();

    GLuint loadTexture(std::string filename);
    asl::model loadObj(std::string fileName);
};

#endif