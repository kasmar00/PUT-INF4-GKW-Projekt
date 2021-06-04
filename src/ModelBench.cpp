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

    float cubeTexCoords[] = {
        1.0f, 0.0f,  //A
        0.0f, 1.0f,  //B
        0.0f, 0.0f,  //C

        1.0f, 0.0f,  //A
        1.0f, 1.0f,  //D
        0.0f, 1.0f,  //B

        1.0f, 0.0f,  //A
        0.0f, 1.0f,  //B
        0.0f, 0.0f,  //C

        1.0f, 0.0f,  //A
        1.0f, 1.0f,  //D
        0.0f, 1.0f,  //B

        1.0f, 0.0f,  //A
        0.0f, 1.0f,  //B
        0.0f, 0.0f,  //C

        1.0f, 0.0f,  //A
        1.0f, 1.0f,  //D
        0.0f, 1.0f,  //B

        1.0f, 0.0f,  //A
        0.0f, 1.0f,  //B
        0.0f, 0.0f,  //C

        1.0f, 0.0f,  //A
        1.0f, 1.0f,  //D
        0.0f, 1.0f,  //B

        1.0f, 0.0f,  //A
        0.0f, 1.0f,  //B
        0.0f, 0.0f,  //C

        1.0f, 0.0f,  //A
        1.0f, 1.0f,  //D
        0.0f, 1.0f,  //B

        1.0f, 0.0f,  //A
        0.0f, 1.0f,  //B
        0.0f, 0.0f,  //C

        1.0f, 0.0f,  //A
        1.0f, 1.0f,  //D
        0.0f, 1.0f,  //B

    };

    for (int i = 0; i < 144; i++) {
        this->verts.push_back(myCubeVertices[i]);
    }
    for (int i = 0; i < 72; i++) {
        this->texCoords.push_back(cubeTexCoords[i]);
    }

    this->vertexCount = 36;
}
