#include <stdio.h>
#include <unistd.h>

#include "Renderer.h"

int main(int argc, char const* argv[]) {
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
