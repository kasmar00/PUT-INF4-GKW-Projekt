#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "AssetManager.h"
#include "Model.h"
#include "ModelStatic.h"

class Renderer {
   private:
    glm::vec3 calcDir(float kat_x, float kat_y);  // rotate the move vector
    AssetManager* assetManager;

   public:
    GLFWwindow* window;
    Renderer(AssetManager* assetManager);
    ~Renderer();

    void initOpenGLProgram();
    void freeOpenGLProgram();

    void loop();
    void drawScene();

    static glm::vec3 speed;      // speed on xyz
    static glm::vec2 speed_rot;  // speed of rotation on xy
    static glm::vec3 pos;        // current position
    static glm::vec2 rot;        // rotation angles
};

#endif  // __RENDERER_H__