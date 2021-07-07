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
        //A
        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        //B
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        //C
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        //D
        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        //E
        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f

    };

    float myCubeTexCoords[] = {
        zero_____, two_third,
        zero_____, one_third,
        one_third, one_third,
        zero_____, two_third,
        one_third, one_third,
        one_third, two_third,
        //B
        one_third, one_third,
        one_third, zero_____,
        two_third, zero_____,
        one_third, one_third,
        two_third, zero_____,
        two_third, one_third,
        //C
        two_third, two_third,
        two_third, one_third,
        one______, one_third,
        two_third, two_third,
        one______, one_third,
        one______, two_third,
        //D
        one_third, one______,
        one_third, two_third,
        two_third, two_third,
        one_third, one______,
        two_third, two_third,
        two_third, one______,
        //E
        one_third, two_third,
        one_third, one_third,
        two_third, one_third,
        one_third, two_third,
        two_third, one_third,
        two_third, two_third

    };

    for (int i = 0; i < 120; i++) {
        this->verts.push_back(myCubeVertices[i]);
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
    M = glm::scale(M, glm::vec3(250, 250, 250));

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
