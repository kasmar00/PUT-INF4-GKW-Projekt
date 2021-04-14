#include "Renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "callbacks.h"

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
    // initShaders();
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glClearColor(0, 0, 0, 1);  //Ustaw kolor czyszczenia bufora kolorów
    glEnable(GL_DEPTH_TEST);   //Włącz test głębokości na pikselach
}

void Renderer::freeOpenGLProgram() {
    // freeShaders();
}

void Renderer::loop() {
    while (!glfwWindowShouldClose(window)) {
        // obliczaj rzeczy
        this->drawScene();
        glfwPollEvents();
    }
}

void Renderer::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Wyczyść bufor koloru i bufor głębokości
    glClearColor(0.5, .9, .5, 1);
    //rysowanie poszególnych elementów

    glfwSwapBuffers(window);  //Skopiuj bufor tylny do bufora przedniego
}
