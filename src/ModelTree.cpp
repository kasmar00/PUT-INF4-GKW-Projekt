#include "ModelTree.h"

#include <fstream>
#include <iostream>
#include <sstream>

ModelTree::ModelTree(glm::vec2 pos, std::vector<float> *verts, std::vector<float> *colors)
    : ModelStaticPoint(pos, verts, colors) {
}
