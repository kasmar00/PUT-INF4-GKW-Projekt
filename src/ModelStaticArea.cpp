#include "ModelStaticArea.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

ModelStaticArea::ModelStaticArea(std::vector<glm::vec2> coords) : ModelStatic() {
    this->coords = coords;

    this->walls = false;
    this->minHeight = 0.0f;
    this->maxHeight = 0.0f;
}

void ModelStaticArea::createCoords() {
    if (walls) {  //ściany tylko wtedy gdy maja być

        enum coordEnum {
            leftDown,
            rightDown,
            rightUp,
            leftUp
        };

        for (uint i = 0; i < this->coords.size() - 1; i++) {
            float dist = glm::distance(coords.data()[i], coords.data()[i + 1]);

            std::vector<glm::vec2> textureSpace = {
                //TODO: have fun with texture coords
                glm::vec2(0.0f, this->minHeight / 4),
                glm::vec2(std::max((int)(dist / 4), 1), this->minHeight / 4),
                glm::vec2(std::max((int)(dist / 4), 1), this->maxHeight / 4),
                glm::vec2(0.0f, this->maxHeight / 4),
            };

            std::vector<glm::vec4> vertexSpace = {
                glm::vec4(coords.data()[i].x, minHeight, coords.data()[i].y, 1),
                glm::vec4(coords.data()[i + 1].x, minHeight, coords.data()[i + 1].y, 1),
                glm::vec4(coords.data()[i + 1].x, maxHeight, coords.data()[i + 1].y, 1),
                glm::vec4(coords.data()[i].x, maxHeight, coords.data()[i].y, 1),
            };

            this->verts.push_back(vertexSpace[leftDown]);  //jeden trójkąt
            this->verts.push_back(vertexSpace[leftUp]);
            this->verts.push_back(vertexSpace[rightUp]);

            this->textureCoords.push_back(textureSpace[leftDown]);
            this->textureCoords.push_back(textureSpace[leftUp]);
            this->textureCoords.push_back(textureSpace[rightUp]);

            this->verts.push_back(vertexSpace[rightDown]);  //drugi trójkąt
            this->verts.push_back(vertexSpace[leftDown]);
            this->verts.push_back(vertexSpace[rightUp]);

            this->textureCoords.push_back(textureSpace[rightDown]);
            this->textureCoords.push_back(textureSpace[leftDown]);
            this->textureCoords.push_back(textureSpace[rightUp]);
        }
    }

    // printf("created coords\n");
}

void ModelStaticArea::addHeight(float min, float max) {
    this->maxHeight = max;
    this->minHeight = min;
}

void ModelStaticArea::addWalls() {
    this->walls = true;
}

void ModelStaticArea::draw(glm::mat4 M) {
    // M = glm::translate(M, glm::vec3(this->locationX, 0, this->locationY));
    // M = glm::rotate(M, this->direction * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));  //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

    glEnableVertexAttribArray(spColored->a("texCoord"));
    glVertexAttribPointer(spColored->a("texCoord"), 2, GL_FLOAT, false, 0, this->textureCoords.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glUniform1i(spColored->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, this->verts.size());

    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("texCoord"));
}