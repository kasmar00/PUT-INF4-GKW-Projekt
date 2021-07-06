#ifndef __SHADER_H__
#define __SHADER_H__

// temporary shader (just so we can see something on the screen)

#include "libs/shaderprogram.h"

extern ShaderProgram* spColored;
extern ShaderProgram* spSkyBox;

void initShaders();
void freeShaders();

#endif  // __SHADER_H__