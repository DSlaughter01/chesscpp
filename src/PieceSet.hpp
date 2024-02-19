#pragma once 
#include <iostream>
#include <string> 
#include <cstdint>
#include <bitset>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

struct PieceSet {

    uint64_t bitboard;
    SDL_Texture* imgTex;

    PieceSet(SDL_Renderer* renderer, std::string imgPath);
};