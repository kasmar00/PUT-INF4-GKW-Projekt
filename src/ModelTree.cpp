#include "ModelTree.h"

#include <fstream>
#include <iostream>
#include <sstream>

ModelTree::ModelTree(glm::vec2 pos, std::vector<float> *verts, std::vector<float> *colors)
    : ModelStaticPoint(pos, verts, colors) {
    // temporary constructor, so we can see something
    // before loading models the proper way
    /*
    //ten kod został przeniesiony do klasy AssetLoader
    using namespace std;

    // struct vert {
    //     float x;
    //     float y;
    //     float z;
    // };
    // glm::vec3 vert;

    fstream file;
    file.open("polygon/assimp/tree.obj", ios::in);
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

    float *vertsa = final_table.data();
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
    float *colorsa = final_colors.data();
    //= {
    //1, 0, 0, 1,
    //0, 1, 0, 1,
    //0, 0, 1, 1
    //};
    cout << final_table.size() << " " << final_colors.size() << endl;
    for (int i = 0; i < f_cnt * 12; i++) {
        this->verts.push_back(vertsa[i]);
        this->colors.push_back(colorsa[i]);
    }
    this->vertexCount = f_cnt * 3;
    */
}
