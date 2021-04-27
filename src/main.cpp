#include <stdio.h>
#include <unistd.h>

#include "DataLoader.h"

#include "Renderer.h"
#include "libs/shaderprogram.h"  //przykład includowania

int main(int argc, char const* argv[]) {

    //AssetManager test code
    DataLoader data;
    data.load_file("data/grass/grass");
    
    Renderer* renderer = new Renderer;

    renderer->loop();
    // sleep(10);

    delete renderer;
    // (down)load data
    // create objects of Model class for all elements from data
    // create Renderer object
    // in loop call draw of draw
    return 0;
}
