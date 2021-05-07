#include "shader.h"

ShaderProgram* spColored;

void initShaders() {
    spColored = new ShaderProgram("./shaders/v_colored.glsl", NULL, "./shaders/f_colored.glsl");
}

void freeShaders() {
    delete spColored;
}