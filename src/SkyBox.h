#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class SkyBox {
   private:
    GLuint tex;
    std::vector<float> verts;
    std::vector<float> texCoords;
    std::vector<float> normals;
    int vertexCount;

   protected:
    SkyBox();
    static SkyBox* skybox_;

   public:
    SkyBox(SkyBox& other) = delete;
    void operator=(const SkyBox&) = delete;
    static SkyBox* GetIntstance();

    void draw();
    void addTexture(GLuint texture);
};

#endif  // __SKYBOX_H__