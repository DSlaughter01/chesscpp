#include <iostream>
#include "Game.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <bitset>
#include "GUI.hpp"
#include "PieceSet.hpp"

int main(int argv, char** args) {

    GUI gui;
    Game game;
    
    game.GameLoop(gui);
    return 0;
}
