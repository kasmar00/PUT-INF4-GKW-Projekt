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

ModelDynamic::ModelDynamic(glm::vec2 pos, GLuint texture, std::vector<float>* verts, std::vector<float>* texCoords, std::vector<float>* normals) {
    this->locationX = pos.x;
    this->locationY = pos.y;
    this->height = 20;
    this->direction = 0;

    this->verts = verts;
    this->texCoords = texCoords;
    this->normals = normals;
    this->vertexCount = verts->size() / 4;
    this->tex = texture;

    this->mapIterator = 1;
    this->map.push_back(std::make_pair(-140.0f, -50.0f));
    this->map.push_back(std::make_pair(-65.0f, -120.0f));
    this->map.push_back(std::make_pair(-128.0f, -192.0f));
    this->map.push_back(std::make_pair(-200.0f, -80.0f));
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
    M = glm::scale(M, glm::vec3(5, 5, 5));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glUniform1i(spColored->u("tex"), 0);

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->verts->data());

    glEnableVertexAttribArray(spColored->a("texCoord"));
    glVertexAttribPointer(spColored->a("texCoord"), 2, GL_FLOAT, false, 0, this->texCoords->data());

    glEnableVertexAttribArray(spColored->a("normal"));
    glVertexAttribPointer(spColored->a("normal"), 4, GL_FLOAT, false, 0, this->normals->data());

    glUniform4f(spColored->u("color"), 1, 1, 1, 1);

    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

    /*
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->wheelVerts.data());
    glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, this->wheelColors.data());

    drawWheel(glm::translate(M, glm::vec3(1.3f, -0.6f, 0.7f)));
    drawWheel(glm::translate(M, glm::vec3(-1.3f, -0.6f, 0.7f)));
    drawWheel(glm::translate(M, glm::vec3(1.3f, -0.6f, -0.7f)));
    drawWheel(glm::translate(M, glm::vec3(-1.3f, -0.6f, -0.7f)));
    */
    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("color"));
    glDisableVertexAttribArray(spColored->a("texCoord"));
    glDisableVertexAttribArray(spColored->a("normal"));
    timer == 360 ? timer = 0 : timer++;
}
