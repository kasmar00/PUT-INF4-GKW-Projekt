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

ModelStaticArea::ModelStaticArea(std::vector<glm::vec2> coords, float minHeight, float maxheight) : ModelStatic() {
    this->coords = coords;

    this->minHeight = minHeight;
    this->maxHeight = maxheight;

    this->createCoords();
}

void ModelStaticArea::createCoords() {
    {
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

            glm::vec4 normal = glm::vec4(glm::cross(glm::vec3(vertexSpace[leftDown] - vertexSpace[rightUp]), glm::vec3(vertexSpace[leftDown] - vertexSpace[leftUp])), 0);
            for (int i = 0; i < 6; i++) {
                this->normals.push_back(normal);
            }
        }
    }
}

void ModelStaticArea::draw(glm::mat4 M) {
    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

    glEnableVertexAttribArray(spColored->a("texCoord"));
    glVertexAttribPointer(spColored->a("texCoord"), 2, GL_FLOAT, false, 0, this->textureCoords.data());

    glEnableVertexAttribArray(spColored->a("normal"));
    glVertexAttribPointer(spColored->a("normal"), 4, GL_FLOAT, false, 0, this->normals.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glUniform1i(spColored->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, this->verts.size());

    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("texCoord"));
    glDisableVertexAttribArray(spColored->a("normal"));
}