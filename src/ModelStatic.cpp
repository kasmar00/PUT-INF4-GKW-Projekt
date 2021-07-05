#include "ModelStatic.h"

void ModelStatic::addTexture(GLuint texture) {
    this->tex = texture;
}

void ModelStatic::setColor(glm::vec4 col) {
    this->color = col;
}
