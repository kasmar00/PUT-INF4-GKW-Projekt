#include "shader.h"

ShaderProgram* spColored;

void initShaders() {
    // spColored = new ShaderProgram("./shaders/v_colored.glsl", NULL, "./shaders/f_colored.glsl");
    spColored = new ShaderProgram("./shaders/v_tex.glsl", NULL, "./shaders/f_tex.glsl");
    printf("shaders!\n");
}

void freeShaders() {
    delete spColored;
}