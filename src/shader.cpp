#include "shader.h"

ShaderProgram* spColored;

void initShaders() {
    // spColored = new ShaderProgram("./shaders/v_colored.glsl", NULL, "./shaders/f_colored.glsl");
    spColored = new ShaderProgram("./shaders/v_textured.glsl", NULL, "./shaders/f_textured.glsl");
    printf("shaders!\n");
}

void freeShaders() {
    delete spColored;
}