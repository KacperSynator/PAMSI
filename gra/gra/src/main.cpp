#include "game/gui.hpp"

#include <cstdlib>
#include <iostream>


// sudo apt install ...
// yay -S sdl2 sdl2_ttf

int main(int argc, char* argv[])
{
    Gui gui;
    if(!gui.init())
    {
        std::cerr << "Game initialization failed\n";
        return EXIT_FAILURE;
    }

    gui.execGame();

    return EXIT_SUCCESS;
}
