#include "SkyBox.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "shader.h"

SkyBox* SkyBox::skybox_ = nullptr;

SkyBox::SkyBox() {
    float myCubeVertices[] = {
        //Ściana 1
        1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,

        //Ściana 2
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        // //Ściana 3
        // -1.0f, -1.0f, -1.0f, 1.0f,
        // 1.0f, -1.0f, 1.0f, 1.0f,
        // 1.0f, -1.0f, -1.0f, 1.0f,

        // -1.0f, -1.0f, -1.0f, 1.0f,
        // -1.0f, -1.0f, 1.0f, 1.0f,
        // 1.0f, -1.0f, 1.0f, 1.0f,

        //Ściana 4
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,

        //Ściana 5
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,

        //Ściana 6
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f

    };

    float myCubeTexCoords[] = {
        //Ściana 1
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        //Ściana 2
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        // //Ściana 3
        // 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        //Ściana 4
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        //Ściana 5
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        //Ściana 6
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f};

    float myCubeNormals[] = {
        //Ściana 1
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,

        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,

        //Ściana 2
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,

        //Ściana 3
        // 0.0f, -1.0f, 0.0f, 0.0f,
        // 0.0f, -1.0f, 0.0f, 0.0f,
        // 0.0f, -1.0f, 0.0f, 0.0f,

        // 0.0f, -1.0f, 0.0f, 0.0f,
        // 0.0f, -1.0f, 0.0f, 0.0f,
        // 0.0f, -1.0f, 0.0f, 0.0f,

        //Ściana 4
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,

        //Ściana 5
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,

        //Ściana 6
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f

    };

    for (int i = 0; i < 120; i++) {
        this->verts.push_back(myCubeVertices[i]);
        this->normals.push_back(myCubeNormals[i]);
    }
    for (int i = 0; i < 60; i++) {
        this->texCoords.push_back(myCubeTexCoords[i]);
    }
    this->vertexCount = 30;

    // printf("Skybox\n");
}

SkyBox* SkyBox::GetIntstance() {
    if (skybox_ == nullptr) {
        skybox_ = new SkyBox();
    }
    return skybox_;
}

void SkyBox::addTexture(GLuint texture) {
    this->tex = texture;
}

void SkyBox::draw() {
    glm::mat4 M = glm::mat4(1);
    M = glm::translate(M, glm::vec3(Renderer::pos.x, 99.9, Renderer::pos.z));  //przeniesienie w miejsce docelowe
    M = glm::scale(M, glm::vec3(250, 100, 250));

    glUniform4f(spSkyBox->u("color"), 1, 1, 1, 1);

    glUniformMatrix4fv(spSkyBox->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spSkyBox->a("vertex"));
    glVertexAttribPointer(spSkyBox->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

    glEnableVertexAttribArray(spSkyBox->a("texCoord"));
    glVertexAttribPointer(spSkyBox->a("texCoord"), 2, GL_FLOAT, false, 0, this->texCoords.data());

    glEnableVertexAttribArray(spSkyBox->a("normal"));
    glVertexAttribPointer(spSkyBox->a("normal"), 4, GL_FLOAT, false, 0, this->normals.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glUniform1i(spSkyBox->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

    glDisableVertexAttribArray(spSkyBox->a("vertex"));
    glDisableVertexAttribArray(spSkyBox->a("texCoord"));
    glDisableVertexAttribArray(spSkyBox->a("normal"));
}
