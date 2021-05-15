#include "DataLoader.h"

DataLoader::DataLoader() {
}

DataLoader::~DataLoader() {
}

std::vector<object_data> DataLoader::load_planar_file(std::string filename, int debug) {
    //TODO harden and error file opening (eg file not existing)
    using namespace std;

    fstream file;
    file.open(filename, ios::in);
    string line;
    vector<object_data> data;
    object_data* current_object = nullptr;
    while (getline(file, line)) {
        if (line == "BEGIN") {
            if (debug) cout << "Begin an object" << endl;
            current_object = new object_data;
        } else if (line == "PROP") {
            getline(file, line);
            if (debug) cout << "Prop count: " << line << endl;
            int cnt = stoi(line);
            for (auto i = 0; i < cnt; i++) {
                getline(file, line);
                stringstream ss;
                ss << line;
                string a, b;
                ss >> a >> b;
                current_object->props.push_back(pair<string, string>(a, b));
                if (debug) cout << a << '\t' << b << endl;
            }
        } else if (line == "COORDS") {
            getline(file, line);
            if (debug) cout << "Coord count: " << line << endl;
            int cnt = stoi(line);
            for (auto i = 0; i < cnt; i++) {
                getline(file, line);
                stringstream ss;
                ss << line;
                double a, b;
                ss >> a >> b;
                current_object->coords.push_back(glm::vec2(a, b));
                if (debug) cout << a << '\t' << b << endl;
            }
        } else if (line == "END") {
            data.push_back(*current_object);
            if (debug) cout << line << endl;
            if (debug)
                for (auto i : current_object->props)
                    cout << i.first << " " << i.second << endl;
        }
    }
    return data;
}

std::vector<object_data> DataLoader::load_point_file(std::string filename, int debug) {
    using namespace std;

    fstream file;
    file.open(filename, ios::in);
    string line;
    vector<object_data> data;
    object_data* current_object = nullptr;

    //prop templates
    vector<string> prop_template;

    while (getline(file, line)) {
        if (line == "BEGIN") {
            if (debug) cout << "Begin point object parsing" << endl;

            // parse the header line to act as 'props'
            // x|y|highway|natural|amenity|height|direction

            string header;
            getline(file, header);
            stringstream header_ss(header);

            while (getline(header_ss, header, '|'))
                prop_template.push_back(header);

        } else if (line == "COORDS") {
            getline(file, line);
            if (debug) cout << "Coord count: " << line << endl;
            int cnt = stoi(line);
            for (auto i = 0; i < cnt; i++) {
                current_object = new object_data;
                getline(file, line);
                stringstream ss(line);
                string prop;
                int count = 0;
                while (getline(ss, prop, '|')) {
                    count += 1;
                    if (count == 1) {
                        glm::vec2 vec;
                        vec.x = stod(prop);
                        getline(ss, prop, '|');
                        vec.y = stod(prop);
                        count += 1;
                        current_object->coords.push_back(vec);

                    } else {
                        if (prop != " ") {
                            if (debug) cout << "Prop: " << prop_template[count - 1] << " " << prop << endl;
                            current_object->props.push_back(pair<string, string>(prop_template[count - 1], prop));
                        }
                    }
                }
                //assert(count == prop_template.size());
                data.push_back(*current_object);
            }
        } else if (line == "END") {
            if (debug) cout << "End of point object parsing\n";
            if (debug)
                for (auto i : data) {
                    //assert(i.coords.size() == 1);
                    cout << "Point object: " << i.coords[0].x << " " << i.coords[0].y << "\nProperties: \n";
                    for (auto j : i.props)
                        cout << "\t" << j.first << " " << j.second << endl;
                    cout << endl;
                }
        }
    }
    return data;
}