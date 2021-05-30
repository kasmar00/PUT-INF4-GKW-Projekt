#include "AssetLoader.h"

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

AssetLoader::AssetLoader() {
}

AssetLoader::~AssetLoader() {
}

std::pair<std::vector<float>, std::vector<float>> AssetLoader::loadObj(std::string fileName) {
    //autor pierwotnej wersji (w ModelTree): Jan Bylicki
    using namespace std;

    fstream file;
    file.open(fileName, ios::in);
    string a;
    vector<glm::vec3> vertexes;
    int v_cnt = 0, f_cnt = 0;
    vector<float> final_table;
    while (getline(file, a)) {
        stringstream line(a);
        stringstream segment;
        string value;
        int index;
        glm::vec3 v;

        switch (a[0] ^ a[1]) {
            case 86:
                v_cnt++;

                //TODO: skip all letters, not 2 characters like an idiot
                line.ignore();
                line.ignore();

                line >> v.x >> v.y >> v.z;
                vertexes.push_back(v);
                break;

            case 70:
                f_cnt++;

                line.ignore();
                line.ignore();
                for (auto i = 0; i < 3; i++) {
                    line >> value;
                    segment = stringstream(value);
                    getline(segment, value, '/');
                    index = stoi(value) - 1;
                    final_table.push_back(vertexes[index].x);
                    final_table.push_back(vertexes[index].y);
                    final_table.push_back(vertexes[index].z);
                    final_table.push_back(1);
                }
                break;

            default:
                break;
        }
    }
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

    //TODO: return format needs to change, but that's a good start
    return std::make_pair(final_table, final_colors);
}