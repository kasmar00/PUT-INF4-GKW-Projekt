#include "shader.h"

ShaderProgram* spColored;
ShaderProgram* spSkyBox;

void initShaders() {
    // spColored = new ShaderProgram("./shaders/v_colored.glsl", NULL, "./shaders/f_colored.glsl");
    spColored = new ShaderProgram("./shaders/v_tex.glsl", NULL, "./shaders/f_tex.glsl");
    spSkyBox = new ShaderProgram("./shaders/v_textured.glsl", NULL, "./shaders/f_textured.glsl");
    printf("shaders!\n");
}

void freeShaders() {
    delete spColored;
    delete spSkyBox;
}