#include "AssetLoader.h"

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

AssetLoader::AssetLoader() {
}

AssetLoader::~AssetLoader() {
}

bool isLetter(char a) {
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
        return 1;
    else
        return 0;
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
                while (isLetter(line.peek()))
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