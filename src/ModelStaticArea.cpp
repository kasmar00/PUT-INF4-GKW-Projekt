#include "ModelStaticArea.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

ModelStaticArea::ModelStaticArea(std::vector<glm::vec2> coords) : ModelStatic() {
    this->coords = coords;
    this->color = glm::vec4(glm::vec4(0.4f, 0.6f, 0.3f, 1));

    this->walls = false;
    this->minHeight = 0.0f;
    this->maxHeight = 0.0f;
}

void ModelStaticArea::createCoords() {
    if (walls) {  //ściany tylko wtedy gdy maja być
        for (uint i = 0; i < this->coords.size() - 1; i++) {
            glm::vec4 ig, ir, jg, jr;  //i is current, j is next, g-ground, r-roof
            ig = glm::vec4(coords.data()[i].x, minHeight, coords.data()[i].y, 1);
            jg = glm::vec4(coords.data()[i + 1].x, minHeight, coords.data()[i + 1].y, 1);
            ir = glm::vec4(coords.data()[i].x, maxHeight, coords.data()[i].y, 1);
            jr = glm::vec4(coords.data()[i + 1].x, maxHeight, coords.data()[i + 1].y, 1);

            this->drawCoords.push_back(ig);  //jeden trójkąt
            this->drawCoords.push_back(ir);
            this->drawCoords.push_back(jr);

            this->drawCoords.push_back(jg);  //drugi trójkąt
            this->drawCoords.push_back(ig);
            this->drawCoords.push_back(jr);

            for (int i = 0; i < 6; i++) {
                glm::vec4 color = glm::vec4(1.0f);
                color.r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                color.g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                color.b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                this->colors.push_back(color);
            }
        }
    }

    //sufit
    //docelowo poprawne dzielenie na trójkąty (również przy kątach>180deg)
    //tymczasowo-wachlarz (recznie)
    glm::vec4 start = glm::vec4(coords.data()[0].x, maxHeight, coords.data()[0].y, 1);
    for (uint i = 1; i < this->coords.size() - 1; i++) {
        glm::vec4 a, b;
        a = glm::vec4(coords.data()[i].x, maxHeight, coords.data()[i].y, 1);
        b = glm::vec4(coords.data()[i + 1].x, maxHeight, coords.data()[i + 1].y, 1);

        this->drawCoords.push_back(start);
        this->drawCoords.push_back(a);
        this->drawCoords.push_back(b);

        for (int i = 0; i < 3; i++)
            this->colors.push_back(this->color);
    }

    //TODO: podłoga???
}

void ModelStaticArea::addHeight(float min, float max) {
    this->maxHeight = max;
    this->minHeight = min;
}

void ModelStaticArea::addWalls() {
    this->walls = true;
}

void ModelStaticArea::addColor(glm::vec4 col) {
    this->color = col;
}

void ModelStaticArea::draw(glm::mat4 M) {
    // M = glm::translate(M, glm::vec3(this->locationX, 0, this->locationY));
    // M = glm::rotate(M, this->direction * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));  //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->drawCoords.data());

    glEnableVertexAttribArray(spColored->a("color"));
    glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, this->colors.data());

    glDrawArrays(GL_TRIANGLES, 0, this->drawCoords.size());

    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("color"));
}