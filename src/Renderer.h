#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Model.h"

class Renderer {
   private:
    // std::vector<Model> models;

   public:
    GLFWwindow *window;
    Renderer();
    ~Renderer();

    void initOpenGLProgram();
    void freeOpenGLProgram();

    void loop();
    void drawScene();
};

#endif  // __RENDERER_H__