#include "ModelStaticPoint.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

void ModelStaticPoint::draw(glm::mat4 M) {
    M = glm::translate(M, glm::vec3(this->locationX, this->locationY, 0));
    M = glm::rotate(M, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));  //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y
    M = glm::rotate(M, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));  //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi X

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

    glEnableVertexAttribArray(spColored->a("color"));
    glVertexAttribPointer(spColored->a("color"), 4, GL_FLOAT, false, 0, this->colors.data());

    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("color"));
}
