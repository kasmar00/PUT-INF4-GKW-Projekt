#include "ModelTree.h"
ModelTree::ModelTree(glm::vec2 pos) : ModelStaticPoint(pos) {
    // temporary constructor, so we can see something
    // before loading models the proper way
    float vertsa[] = {
        0, 1, 0, 1,
        0, -1, 0, 1,
        1.5, 0, -1, 1,
        0, 1, 0, 1,
        0, -1, 0, 1,
        -1.5, 0, -1, 1};

    float colorsa[] = {
        1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1,
        1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1};

    for (int i = 0; i < 24; i++) {
        this->verts.push_back(vertsa[i]);
        this->colors.push_back(colorsa[i]);
    }
    this->vertexCount = 6;
}
