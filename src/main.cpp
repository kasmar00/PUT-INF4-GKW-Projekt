#include <stdio.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>

#include "AssetManager.h"
#include "Renderer.h"
#include "libs/shaderprogram.h"  //przykład includowania

int main(int argc, char const* argv[]) {
    AssetManager manager;
    Renderer renderer(&manager);

    manager.generate_models_from_path("data/export/");

    renderer.loop();

    return 0;
}
