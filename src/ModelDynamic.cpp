//glm::vec3 Renderer::pos = glm::vec3(0.0f, 0.0f, -15.0f);  // początkowa pozycja
#include "ModelDynamic.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "shader.h"

ModelDynamic::ModelDynamic(glm::vec2 pos) {
    this->locationX = pos.x;
    this->locationY = pos.y;
    this->height = 1;
    this->direction = 0;

    // temporary data, so we can see something
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
        this->bodyVerts.push_back(myCubeVertices[i]);
        this->bodyColors.push_back(myCubeColors[i]);
        this->wheelVerts.push_back(myCubeVertices[i]);
        this->wheelColors.push_back(myCubeColors[i]);
    }
    this->bodyVertexCount = 36;
    this->wheelVertexCount = 36;

    this->mapIterator = 1;
    this->map.push_back(std::make_pair(0, -15));
    this->map.push_back(std::make_pair(10, 3));
    this->map.push_back(std::make_pair(0, 0));

    this->rotation = (float)atan2(this->locationX - map[this->mapIterator % this->map.size()].first, this->locationY - map[this->mapIterator % this->map.size()].second);

    /*
    GKW, aprox cords for CW loop (need to push it to vector map)
        -990.0f, 1, 285.0f
        -800.0f, 1, -35.0f
        -762.0f, 1, -11.0f
        -676.0f, 1, -5.0f
        -595.0f, 1, -10.0f
        -582.0f, 1, 90.0f
        -597.0f, 1, 158.0f
        -714.0f, 1, 442.0f
        -905.0f, 1, 335.0f
        -925.0f, 1, 320.0f

    */
}

void ModelDynamic::setHeight(float height) {
    this->height = height;
}

void ModelDynamic::setDirection(int direction) {
    this->direction = direction;
}

void ModelDynamic::draw(glm::mat4 M) {
    M = glm::translate(M, glm::vec3(this->locationX, this->height, this->locationY));
    if (this->locationX != map[this->mapIterator % this->map.size()].first)
        this->locationX += (this->locationX - map[this->mapIterator % this->map.size()].first) > 0 ? -0.0625f : 0.0625f;
    if (this->locationY != map[this->mapIterator % this->map.size()].second)
        this->locationY += (this->locationY - map[this->mapIterator % this->map.size()].second) > 0 ? -0.0625f : 0.0625f;
    if (this->locationX == map[this->mapIterator % this->map.size()].first && this->locationY == map[mapIterator % this->map.size()].second)
        this->mapIterator == this->map.size() ? this->mapIterator = 0 : this->mapIterator++;

    M = glm::rotate(M, 25 * (90 + timer) * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->bodyVerts.data());

    glEnableVertexAttribArray(spColored->a("color"));
    glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, this->bodyColors.data());

    glDrawArrays(GL_TRIANGLES, 0, this->bodyVertexCount);

    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->wheelVerts.data());
    glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, this->wheelColors.data());

    drawWheel(glm::translate(M, glm::vec3(1.3f, -0.6f, 0.7f)));
    drawWheel(glm::translate(M, glm::vec3(-1.3f, -0.6f, 0.7f)));
    drawWheel(glm::translate(M, glm::vec3(1.3f, -0.6f, -0.7f)));
    drawWheel(glm::translate(M, glm::vec3(-1.3f, -0.6f, -0.7f)));
    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("color"));
    timer == 360 ? timer = 0 : timer++;
}

void ModelDynamic::drawWheel(glm::mat4 M) {
    glm::mat4 Mw = glm::rotate(M, 2 * (90 + timer) * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
    Mw = glm::scale(Mw, glm::vec3(0.3f, 0.3f, 0.3f));
    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(Mw));

    glDrawArrays(GL_TRIANGLES, 0, this->wheelVertexCount);
}