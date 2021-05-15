#include <stdio.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>

#include "AssetManager.h"
#include "Renderer.h"
#include "libs/shaderprogram.h"  //przykład includowania

int main(int argc, char const* argv[]) {
    srand(static_cast<unsigned>(time(0)));  //initialize random generator (used in random coloring)

    AssetManager manager;
    manager.generate_models_from_path("data/export/");

    Renderer renderer(&manager);

    renderer.loop();

    return 0;
}
