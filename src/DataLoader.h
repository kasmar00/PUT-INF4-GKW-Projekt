#ifndef __DATA_LOADER_H__
#define __DATA_LOADER_H__

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef struct object_data {
    std::vector<std::pair<std::string, std::string>> props;
    std::vector<glm::vec2> coords;
};

class DataLoader {
   private:
   public:
    DataLoader();
    ~DataLoader();

    std::vector<object_data> load_file(std::string filename, int debug = 0);
};

#endif