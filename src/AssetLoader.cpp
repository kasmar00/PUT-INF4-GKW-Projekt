#include "AssetLoader.h"


#include <iostream>
#include <vector>

#include "libs/lodepng.h"

GLuint texGlobal = 0;

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

AssetLoader::AssetLoader() {
    // Sprawdzenie liczby jednostek teksturujących w karcie graficznej
    printf("Constructed asset loader at: %p\n", this);
}

AssetLoader::~AssetLoader() {
    for (auto i : this->allTextures) {
        glDeleteTextures(1, &i);
    }

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
    if (error)
        printf("error: %d\n", error);

    printf("liczba bajtow tekstury %ld\n", image.size());

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex);             //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex);  //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glGenerateMipmap(GL_TEXTURE_2D);

    //TODO: pobawić się mip mapami
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    printf("Loadeed texture %s\n", filename.c_str());

    this->allTextures.push_back(tex);
    // texGlobal = tex;

    return tex;
}

asl::model AssetLoader::loadObj(std::string fileName) {
    //autor pierwotnej wersji (w ModelTree): Jan Bylicki
    using namespace std;
    asl::model model;
    asl::mesh mesh;
    fstream file;
    file.open(fileName, ios::in);
    string a;
    vector<glm::vec3> vertexes;
    int v_cnt = 0, f_cnt = 0;
    bool skip_flag = true;
    vector<float> vert;
    while (getline(file, a)) {
        stringstream line(a);
        stringstream segment;
        string value;
        int index;
        glm::vec3 v;

        switch (a[0] ^ a[1]) {
            case 79:  // 'o' ^ ' '
                if (!skip_flag) {
                    mesh.push_back(vert);
                    model.push_back(mesh);
                    vert = vector<float>();
                    mesh = vector<vector<float>>();
                }
                skip_flag = false;
                break;
            case 86:  // 'v' ^ ' '
                v_cnt++;

                //TODO: skip all letters, not 2 characters like an idiot - DONE
                //TESTME
                while (isalpha(line.peek()))
                    line.ignore();

                line >> v.x >> v.y >> v.z;
                vertexes.push_back(v);
                break;

            case 70:  // 'f' ^ ' '
                f_cnt++;

                line.ignore();
                line.ignore();
                for (auto i = 0; i < 3; i++) {
                    line >> value;
                    segment = stringstream(value);
                    getline(segment, value, '/');
                    index = stoi(value) - 1;
                    vert.push_back(vertexes[index].x);
                    vert.push_back(vertexes[index].y);
                    vert.push_back(vertexes[index].z);
                    vert.push_back(1);
                }
                break;

            default:
                break;
        }
    }
    mesh.push_back(vert);
    model.push_back(mesh);
    cout << v_cnt << " " << f_cnt << endl;

    vector<float> final_colors;
    for (auto i = 0; i < f_cnt; i++) {
        final_colors.push_back(1);
        final_colors.push_back(0);
        final_colors.push_back(0);
        final_colors.push_back(1);

        final_colors.push_back(0);
        final_colors.push_back(1);
        final_colors.push_back(0);
        final_colors.push_back(1);

        final_colors.push_back(0);
        final_colors.push_back(0);
        final_colors.push_back(1);
        final_colors.push_back(1);
    }
    for (int i = 0; i < model.size(); i++) {
        cout << "Pushing color " << i << endl;
        model[i].push_back(final_colors);
    }

    cout << "Model size:" << model.size() << "\nZero element size:" << model[0].size() << "\nZero v size:" << model[0][0].size() << "\nZero color(vt) size:" << model[0][1].size() << endl;
    //TODO: return format needs to change, but that's a good start
    return model;
}
