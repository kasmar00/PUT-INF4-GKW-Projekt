#ifndef __DATA_LOADER_H__
#define __DATA_LOADER_H__

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct object_data {
    std::unordered_map<std::string, std::string> props;
    std::vector<glm::vec2> coords;
};

class DataLoader {
   private:
   public:
    DataLoader();
    ~DataLoader();

    std::vector<object_data> load_planar_file(std::string filename, int debug = 0);
    std::vector<object_data> load_point_file(std::string filename, int debug = 0);
};

#endif