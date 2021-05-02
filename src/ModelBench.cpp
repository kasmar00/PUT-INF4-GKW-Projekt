#include "ModelBench.h"
ModelBench::ModelBench(glm::vec2 pos) : ModelStaticPoint(pos) {
    // temporary constructor, so we can see something
    // before loading models the proper way
    float myCubeVertices[] = {
        //Ściana 1
        1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,

        //Ściana 2
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        //Ściana 3
        -1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,

        //Ściana 4
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,

        //Ściana 5
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,

        //Ściana 6
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f

    };

    float myCubeColors[] = {
        //Ściana 1
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        //Ściana 2
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        //Ściana 3
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        //Ściana 4
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        //Ściana 5
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        //Ściana 6
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

    for (int i = 0; i < 144; i++) {
        this->verts.push_back(myCubeVertices[i]);
        this->colors.push_back(myCubeColors[i]);
    }
    this->vertexCount = 36;
}
