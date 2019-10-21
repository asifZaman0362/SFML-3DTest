#include <GL/gl.h>
#include <SFML/OpenGL.hpp>
#include "Engine.h"
#include <iostream>

int main () {
    Settings settings("Window", 800, 480, 24, 0, false, false, false, false);
    Game game(settings);
    game.Start();

    return 0;
}

