#include <GL/gl.h>
#include <SFML/OpenGL.hpp>
#include "Engine.h"
#include <iostream>
#include "ModelLoader.h"

int main () {
    //Settings settings("Window", 800, 600, 24, 0, true, false, false, false);
    //Game game(settings);
    //game.Start();

    float* data = new float[10];
    LoadModel("box.obj", data);
    delete[] data;

    return 0;
    
}

