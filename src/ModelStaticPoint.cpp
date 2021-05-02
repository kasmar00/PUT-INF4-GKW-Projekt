#include "ModelStaticPoint.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "shader.h"

ModelStaticPoint::ModelStaticPoint(glm::vec2 pos) {
    this->locationX = pos.x;
    this->locationY = pos.y;
    this->height = 2;
    this->direction = 0;
}

void ModelStaticPoint::setHeight(float height) {
    this->height = height;
    //TODO maybe transfer this function to ModelStatic, because it can't be accessed from polymorfic
    // alternatively use casting to ModelStaticPoint or Model[Bench|Tree]
}

void ModelStaticPoint::setDirection(int direction) {
    this->direction = direction;
}
void ModelStaticPoint::draw(glm::mat4 M) {
    M = glm::translate(M, glm::vec3(this->locationX, 0, this->locationY));
    M = glm::rotate(M, this->direction * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));  //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

    glEnableVertexAttribArray(spColored->a("color"));
    glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, this->colors.data());

    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("color"));
}
