#include "Renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ModelBench.h"
#include "ModelTree.h"
#include "callbacks.h"
#include "constants.h"
#include "shader.h"

glm::vec3 Renderer::speed = glm::vec3(0, 0, 0);
glm::vec2 Renderer::speed_rot = glm::vec2(0, 0);

glm::vec3 Renderer::pos = glm::vec3(0.0f, 0.0f, -15.0f);  // początkowa pozycja
glm::vec2 Renderer::rot = glm::vec2(0.0f, 0.0f);

float Renderer::aspectRatio = 1.0f;

Renderer::Renderer(/* args */) {
    glfwSetErrorCallback(callbacks::error_callback);  //Zarejestruj procedurę obsługi błędów

    if (!glfwInit()) {  //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window)  //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
        fprintf(stderr, "Nie można utworzyć okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);  //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1);             //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    if (glewInit() != GLEW_OK) {  //Zainicjuj bibliotekę GLEW
        fprintf(stderr, "Nie można zainicjować GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram();  //Operacje inicjujące
}

Renderer::~Renderer() {
    freeOpenGLProgram();

    glfwDestroyWindow(window);  //Usuń kontekst OpenGL i okno
    glfwTerminate();            //Zwolnij zasoby zajęte przez GLFW
}

void Renderer::initOpenGLProgram() {
    initShaders();

    glClearColor(0, 0, 0, 1);  //Ustaw kolor czyszczenia bufora kolorów
    glEnable(GL_DEPTH_TEST);   //Włącz test głębokości na pikselach

    glfwSetKeyCallback(window, callbacks::key_callback);  // procedura obsługi klawiatury

    glfwSetWindowSizeCallback(window, callbacks::window_size);

    //some example models
    ModelBench* a = new ModelBench(glm::vec2(2, 1));
    a->setDirection(45);
    this->models.push_back(a);
    ModelBench* b = new ModelBench(glm::vec2(5, 1));
    b->setDirection(90);
    this->models.push_back(b);

    this->models.push_back(new ModelTree(glm::vec2(2, -3)));
    this->models.push_back(new ModelBench(glm::vec2(-2, -1)));
    ((ModelBench*)models.back())->setDirection(30);
}

void Renderer::freeOpenGLProgram() {
    freeShaders();
}

glm::vec3 Renderer::calcDir(float kat_x, float kat_y) {
    //Author: dr Witold Andrzejewski (GKW Lecture 2021-03-24)
    glm::vec4 dir = glm::vec4(0, 0, 1, 0);
    glm::mat4 M = glm::rotate(glm::mat4(1.0f), kat_y, glm::vec3(0, 1, 0));
    M = glm::rotate(M, kat_x, glm::vec3(1, 0, 0));
    dir = M * dir;
    return glm::vec3(dir);
}

void Renderer::loop() {
    glm::vec3 dir = glm::vec3(0, 0, 0);
    glm::vec3 dir_left = glm::vec3(0, 0, 0);

    while (!glfwWindowShouldClose(window)) {
        rot.x += Renderer::speed_rot.x * glfwGetTime();  //rotate the camera on x axis (up-down)
        rot.y += Renderer::speed_rot.y * glfwGetTime();  //rotate on y axis (left-right)

        dir = calcDir(0, rot.y);                //calculate rotated movement vector
        dir_left = calcDir(0, rot.y + PI / 2);  //=||= but on perpendicular movement

        pos.y += 10 * glfwGetTime() * speed.y;  //move on y axis (up-down), not dependent on camera
        //move on x,z axis, dependent on camera rotation
        pos.x += 10 * glfwGetTime() * (speed.z * dir.x + speed.x * dir_left.x);
        pos.z += 10 * glfwGetTime() * (speed.z * dir.z + speed.x * dir_left.z);

        glfwSetTime(0);
        this->drawScene();
        glfwPollEvents();
    }
}

void Renderer::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Wyczyść bufor koloru i bufor głębokości
    glClearColor(0.5, .9, .5, 1);

    spColored->use();

    glm::mat4 V = glm::lookAt(pos, pos + calcDir(rot.x, rot.y), glm::vec3(0.0f, 1.0f, 0.0f));  //macierz widoku
    glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f);             //macierz rzutowania
    glUniformMatrix4fv(spColored->u("P"), 1, false, glm::value_ptr(P));                        //ładowanie macierzy rzutowania
    glUniformMatrix4fv(spColored->u("V"), 1, false, glm::value_ptr(V));                        //ładowanie macierzy widoku

    //rysowanie poszczególnych elementów
    for (auto i : this->models) {
        i->draw(glm::mat4(1.0f));
    }
    glfwSwapBuffers(window);  //Skopiuj bufor tylny do bufora przedniego
}
