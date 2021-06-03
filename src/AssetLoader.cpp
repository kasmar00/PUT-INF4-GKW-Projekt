#include "AssetLoader.h"

#include <iostream>
#include <vector>

#include "libs/lodepng.h"

GLuint texGlobal = 0;

AssetLoader::AssetLoader() {
    // Sprawdzenie liczby jednostek teksturujących w karcie graficznej
    GLint textureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
    printf("Liczba jednostek teksturujących: %d\n", textureUnits);
    printf("constructed asset loader at: %p\n", this);
}

AssetLoader::~AssetLoader() {
    // for (auto i : this->allTextures) {
    //     glDeleteTextures(1, &i);
    // }

    printf("Deleting asset loader\n");
}

GLuint AssetLoader::loadTexture(std::string filename) {
    GLuint tex;

    glActiveTexture(GL_TEXTURE0);  //powoduje segfault

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;  //Alokuj wektor do wczytania obrazka
    unsigned width, height;            //Zmienne do których wczytamy wymiary obrazka

    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename.c_str());
    printf("error: %d\n", error);

    printf("liczba bajtow tekstury %ld\n", image.size());

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex);             //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex);  //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    printf("Loadeed texture %s\n", filename.c_str());

    this->allTextures.push_back(tex);

    return tex;
}
